/*
  ==============================================================================

    XYPad.h
    Created: 7 Apr 2022 12:07:24am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
struct XYPad : juce::Component
{
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Image canvas;
};
