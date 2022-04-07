/*
  ==============================================================================

    RotaryControl.h
    Created: 6 Apr 2022 11:23:20pm
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
struct RotaryControl : juce::Slider
{
    RotaryControl(const double& rangeMin, const double& rangeMax);
    ~RotaryControl() { setLookAndFeel(nullptr); }
    void paint (juce::Graphics&) override;
    
private:
    CustomLookAndFeel lnf;
};
