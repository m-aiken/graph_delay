/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RotaryControl.h"

//==============================================================================
/**
*/
class JuceDelayV2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JuceDelayV2AudioProcessorEditor (JuceDelayV2AudioProcessor&);
    ~JuceDelayV2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceDelayV2AudioProcessor& audioProcessor;
    
    juce::Slider timeSlider, feedbackSlider, wetSlider, drySlider;
    
    RotaryControl timeRotary     { "Delay Time",   0.0, 1000.0 },
                  feedbackRotary { "Feedback",     0.0,    1.0 },
                  wetRotary      { "Wet",        -60.0,    0.0 },
                  dryRotary      { "Dry",        -60.0,    0.0 };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDelayV2AudioProcessorEditor)
};
