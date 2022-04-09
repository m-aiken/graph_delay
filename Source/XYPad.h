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
struct Canvas : juce::Component
{
    void paint(juce::Graphics& g) override;
};

//==============================================================================
struct Thumb : juce::Component
{
    void paint(juce::Graphics& g) override;
    juce::Value& getXValue() { return xValue; };
    juce::Value& getYValue() { return yValue; };
private:
    juce::Value xValue, yValue;
};

//==============================================================================
struct XYPad : juce::Component
{
    XYPad();
    void paint(juce::Graphics& g) override;
    void resized() override;
    juce::Value& getThumbXValue() { return thumb.getXValue(); };
    juce::Value& getThumbYValue() { return thumb.getYValue(); };
private:
    Canvas canvas;
    Thumb thumb;
};
