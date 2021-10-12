/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceDelayV2AudioProcessor::JuceDelayV2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

JuceDelayV2AudioProcessor::~JuceDelayV2AudioProcessor()
{
}

//==============================================================================
const juce::String JuceDelayV2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceDelayV2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceDelayV2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceDelayV2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceDelayV2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceDelayV2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceDelayV2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceDelayV2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JuceDelayV2AudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceDelayV2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JuceDelayV2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sRate = sampleRate;

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    delayLine.reset();
    delayLine.prepare(spec);

    smoother.reset(sampleRate, 0.001);
    smoother.setCurrentAndTargetValue(apvts.getRawParameterValue ("TIME")->load());
}

void JuceDelayV2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceDelayV2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceDelayV2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    smoother.setTargetValue(apvts.getRawParameterValue ("TIME")->load());

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelDataRead  = buffer.getReadPointer  (channel);
        auto* channelDataWrite = buffer.getWritePointer (channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            smoother.getNextValue();

            channelDataWrite[i] = addDelay(channel, channelDataRead[i]);
        }
    }
}

float JuceDelayV2AudioProcessor::addDelay(int channel, float inputSample)
{
    auto delayTime     = apvts.getRawParameterValue ("TIME")->load();
    auto delayFeedback = apvts.getRawParameterValue ("FEEDBACK")->load();
    auto delayWetLevel = apvts.getRawParameterValue ("WET")->load();
    auto delayDryLevel = apvts.getRawParameterValue ("DRY")->load();

    auto delaySample = delayLine.popSample (channel, static_cast<int> (sRate * (delayTime / 1000.f)));

    auto delayLineInputSample = std::tanh (inputSample + delayFeedback * delaySample);

    delayLine.pushSample (channel, delayLineInputSample);

    auto wet = juce::Decibels::decibelsToGain (delayWetLevel);
    auto dry = juce::Decibels::decibelsToGain (delayDryLevel);

    return (inputSample * dry) + (delaySample * wet);
}

//==============================================================================
bool JuceDelayV2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JuceDelayV2AudioProcessor::createEditor()
{
    return new JuceDelayV2AudioProcessorEditor (*this);
}

//==============================================================================
void JuceDelayV2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceDelayV2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout JuceDelayV2AudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>("TIME",
                                                           "Delay Time",
                                                           juce::NormalisableRange<float>(0.f, 1000.f, 1.f),
                                                           400.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("FEEDBACK",
                                                           "Feedback",
                                                           juce::NormalisableRange<float>(0.f, 1.f, 0.01f),
                                                           0.5f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("WET",
                                                           "Wet",
                                                           juce::NormalisableRange<float>(-60.f, 0.f, 1.f),
                                                           -6.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("DRY",
                                                           "Dry",
                                                           juce::NormalisableRange<float>(-60.f, 0.f, 1.f),
                                                           -6.f));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceDelayV2AudioProcessor();
}
