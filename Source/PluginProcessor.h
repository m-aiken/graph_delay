/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class JuceDelayV2AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    JuceDelayV2AudioProcessor();
    ~JuceDelayV2AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float processDelay(int& channel, float& inputSample);
    
    static juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();

    juce::AudioProcessorValueTreeState apvts {*this, nullptr, "Parameters", getParameterLayout()};
    
private:
    double sRate { 44100 };
    
    float delayTime, delayFeedback, delayWetLevel, delayDryLevel;
    float delaySignal;
    
    using smoother = juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>;
    smoother delayTimeSmoothed [2] { smoother(0.f), smoother(0.f) };
    
    using delayLine = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>;
    
    delayLine delayLines [2] { delayLine(44100), delayLine(44100) };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDelayV2AudioProcessor)
};
