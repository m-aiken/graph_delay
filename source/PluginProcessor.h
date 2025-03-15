#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class PluginProcessor : public juce::AudioProcessor
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;

    double getTailLengthSeconds() const override;

    int                getNumPrograms() override;
    int                getCurrentProgram() override;
    void               setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void               changeProgramName(int index, const juce::String& new_name) override;

    void prepareToPlay(double sample_rate, int samples_per_block) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages) override;

    bool                        hasEditor() const override;
    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& dest_data) override;
    void setStateInformation(const void* data, int size_in_bytes) override;

    juce::AudioProcessorValueTreeState& getApvts();
    float                               getParamValue(const GraphDelay::ParamId& param_id) const;

private:
    float processDelay(const int channel, const float input_sample);

    static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();

    juce::AudioProcessorValueTreeState apvts_;

    float delay_time_;
    float delay_feedback_;
    float delay_wet_level_;
    float delay_dry_level_;
    float delay_signal_;

    juce::dsp::DelayLine< float >               delay_line_;
    std::vector< juce::SmoothedValue< float > > smoothed_delay_times_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
