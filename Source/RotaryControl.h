/*
  ==============================================================================

    RotaryControl.h
    Created: 6 Apr 2022 11:23:20pm
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
struct RotaryControl : juce::Component
{
    RotaryControl(const juce::String& labelText, const double& rangeMin, const double& rangeMax);
    void paint (juce::Graphics&) override;
    void resized() override;
    juce::Value& getValueObject() { return rotary.getValueObject(); }
    
private:
    juce::Slider rotary;
    juce::Label label;
};
