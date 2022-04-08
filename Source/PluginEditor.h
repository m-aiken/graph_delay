/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ColourMap.h"
#include "RotaryControl.h"
#include "XYPad.h"

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
    
    void formatLabel(juce::Label& label, const juce::String& labelText);
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceDelayV2AudioProcessor& audioProcessor;
    
    RotaryControl timeRotary     {   0.0, 1000.0 },
                  feedbackRotary {   0.0,    1.0 },
                  wetRotary      { -60.0,    0.0 },
                  dryRotary      { -60.0,    0.0 };
    
    juce::Label timeLabel, feedbackLabel, wetLabel, dryLabel;
    
    XYPad xyPad;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDelayV2AudioProcessorEditor)
};
