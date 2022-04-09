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
};

//==============================================================================
struct Overlay : juce::Component
{
    Overlay();
    void paint(juce::Graphics& g) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    juce::Value& getXValue() { return xValue; };
    juce::Value& getYValue() { return yValue; };
private:
    juce::Value xValue, yValue;
    Thumb thumb;
};

//==============================================================================
struct XYContainer : juce::Component
{
    XYContainer();
    void resized() override;
    
    juce::Value& getXValue() { return overlay.getXValue(); };
    juce::Value& getYValue() { return overlay.getYValue(); };
private:
    Canvas canvas;
    Overlay overlay;
};
