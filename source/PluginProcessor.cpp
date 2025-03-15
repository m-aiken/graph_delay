#include "PluginProcessor.h"
#include "PluginEditor.h"

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , apvts_(*this, nullptr, "APVTS", getParameterLayout())
    , delay_time_(0.f)
    , delay_feedback_(0.f)
    , delay_wet_level_(0.f)
    , delay_dry_level_(0.f)
    , delay_signal_(0.f)
{
}

/*---------------------------------------------------------------------------
**
*/
PluginProcessor::~PluginProcessor()
{
}

/*---------------------------------------------------------------------------
**
*/
const juce::String
PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::acceptsMidi() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::producesMidi() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::isMidiEffect() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
double
PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

/*---------------------------------------------------------------------------
**
*/
int
PluginProcessor::getNumPrograms()
{
    return 1;  // NB: some hosts don't cope very well if you tell them there are 0 programs,
               // so this should be at least 1, even if you're not really implementing programs.
}

/*---------------------------------------------------------------------------
**
*/
int
PluginProcessor::getCurrentProgram()
{
    return 0;
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

/*---------------------------------------------------------------------------
**
*/
const juce::String
PluginProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);

    return {};
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::changeProgramName(int index, const juce::String& new_name)
{
    juce::ignoreUnused(index, new_name);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::prepareToPlay(double sample_rate, int samples_per_block)
{
    delay_time_      = getParamValue(GraphDelay::TIME);
    delay_feedback_  = getParamValue(GraphDelay::FEEDBACK);
    delay_wet_level_ = juce::Decibels::decibelsToGain(getParamValue(GraphDelay::WET_LEVEL));
    delay_dry_level_ = juce::Decibels::decibelsToGain(getParamValue(GraphDelay::DRY_LEVEL));

    const int input_channels = getTotalNumInputChannels();

    juce::dsp::ProcessSpec spec;
    spec.sampleRate       = sample_rate;
    spec.maximumBlockSize = samples_per_block;
    spec.numChannels      = input_channels;

    delay_line_.prepare(spec);
    delay_line_.setMaximumDelayInSamples(static_cast< int >(sample_rate) * 2);

    smoothed_delay_times_.resize(input_channels);

    for (int i = 0; i < input_channels; ++i) {
        smoothed_delay_times_.at(i).reset(sample_rate, 0.01);
        smoothed_delay_times_.at(i).setCurrentAndTargetValue(0.f);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Some plugin hosts will only support mono or stereo output bus layouts.
    const bool mono_out   = layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono();
    const bool stereo_out = layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();

    // We want the input and output layouts to match (i.e. mono in --> mono out or stereo in --> stereo out).
    const bool in_matches_out = layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();

    return (mono_out || stereo_out) && in_matches_out;
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages)
{
    juce::ignoreUnused(midi_messages);

    juce::ScopedNoDenormals no_denormals;
    const int               num_input_channels  = getTotalNumInputChannels();
    const int               num_output_channels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, clear any output channels that don't contain input data.
    for (auto i = num_input_channels; i < num_output_channels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    for (int channel = 0; channel < num_input_channels; ++channel) {
        for (int sample_index = 0; sample_index < buffer.getNumSamples(); ++sample_index) {
            const float input_sample = buffer.getSample(channel, sample_index);

            delay_time_      = getParamValue(GraphDelay::TIME);
            delay_feedback_  = getParamValue(GraphDelay::FEEDBACK);
            delay_wet_level_ = juce::Decibels::decibelsToGain(getParamValue(GraphDelay::WET_LEVEL));
            delay_dry_level_ = juce::Decibels::decibelsToGain(getParamValue(GraphDelay::DRY_LEVEL));

            smoothed_delay_times_.at(channel).setTargetValue(delay_time_);
            delay_time_ = smoothed_delay_times_.at(channel).getNextValue();

            delay_signal_ = processDelay(channel, input_sample);

            const float new_value = (input_sample * delay_dry_level_) + (delay_signal_ * delay_wet_level_);

            buffer.setSample(channel, sample_index, new_value);
        }
    }
}

/*---------------------------------------------------------------------------
**
*/
bool
PluginProcessor::hasEditor() const
{
    return true;
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessorEditor*
PluginProcessor::createEditor()
{
    return new PluginEditor(*this);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::getStateInformation(juce::MemoryBlock& dest_data)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream mos(dest_data, true);
    apvts_.state.writeToStream(mos);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginProcessor::setStateInformation(const void* data, int size_in_bytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    auto tree = juce::ValueTree::readFromData(data, size_in_bytes);

    if (tree.isValid()) {
        apvts_.replaceState(tree);
    }
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessorValueTreeState&
PluginProcessor::getApvts()
{
    return apvts_;
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::getParamValue(const GraphDelay::ParamId& param_id) const
{
    const juce::RangedAudioParameter* param = apvts_.getParameter(param_id);

    return (param != nullptr) ? param->convertFrom0to1(param->getValue()) : 0.f;
}

/*---------------------------------------------------------------------------
**
*/
float
PluginProcessor::processDelay(const int channel, const float input_sample)
{
    const auto srate_f          = static_cast< float >(getSampleRate());
    const auto delay_in_samples = (srate_f * delay_time_) / 1000.f;
    const auto delay_sample     = delay_line_.popSample(channel, delay_in_samples);
    const auto sample_to_push   = std::tanh(input_sample + delay_feedback_ * delay_sample);

    delay_line_.pushSample(channel, sample_to_push);

    return delay_sample;
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessorValueTreeState::ParameterLayout
PluginProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    const auto time_range     = juce::NormalisableRange< float >(GraphDelay::DELAY_MS_MIN,
                                                             GraphDelay::DELAY_MS_MAX,
                                                             GraphDelay::DELAY_INTERVAL);
    const auto feedback_range = juce::NormalisableRange< float >(GraphDelay::FEEDBACK_MIN,
                                                                 GraphDelay::FEEDBACK_MAX,
                                                                 GraphDelay::FEEDBACK_INTERVAL);
    const auto wet_range      = juce::NormalisableRange< float >(GraphDelay::DB_MIN,
                                                            GraphDelay::DB_MAX,
                                                            GraphDelay::DB_INTERVAL);
    const auto dry_range      = juce::NormalisableRange< float >(GraphDelay::DB_MIN,
                                                            GraphDelay::DB_MAX,
                                                            GraphDelay::DB_INTERVAL);

    layout.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(GraphDelay::TIME, 1),
                                                             GraphDelay::TIME,
                                                             time_range,
                                                             GraphDelay::DELAY_MS_DEFAULT));

    layout.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(GraphDelay::FEEDBACK, 1),
                                                             GraphDelay::FEEDBACK,
                                                             feedback_range,
                                                             GraphDelay::FEEDBACK_DEFAULT));

    layout.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(GraphDelay::WET_LEVEL, 1),
                                                             GraphDelay::WET_LEVEL,
                                                             wet_range,
                                                             GraphDelay::DB_DEFAULT_WET_LEVEL));

    layout.add(std::make_unique< juce::AudioParameterFloat >(juce::ParameterID(GraphDelay::DRY_LEVEL, 1),
                                                             GraphDelay::DRY_LEVEL,
                                                             dry_range,
                                                             GraphDelay::DB_DEFAULT_DRY_LEVEL));

    return layout;
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessor* JUCE_CALLTYPE
createPluginFilter()
{
    return new PluginProcessor();
}

/*---------------------------------------------------------------------------
** End of File
*/
