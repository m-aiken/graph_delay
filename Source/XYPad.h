/*
  ==============================================================================

    XYPad.h
    Created: 7 Apr 2022 12:07:24am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ColourMap.h"

//==============================================================================
struct Thumb : juce::Component
{
    void paint (juce::Graphics&) override;
};

//==============================================================================
struct XYPad : juce::Component
{
    XYPad();
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Image canvas;
    
    Thumb thumb;
};
