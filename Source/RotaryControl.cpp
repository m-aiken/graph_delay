/*
  ==============================================================================

    RotaryControl.cpp
    Created: 6 Apr 2022 11:23:20pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "RotaryControl.h"

//==============================================================================
RotaryControl::RotaryControl(const double& rangeMin, const double& rangeMax)
{
    setLookAndFeel(&lnf);
    setRange(rangeMin, rangeMax);
//    setSliderStyle(juce::Slider::SliderStyle::Rotary);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
}

void RotaryControl::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    auto diameter = bounds.getWidth() * 0.9f;
    auto radius = diameter / 2;
    
    auto startAngle = juce::degreesToRadians(180.f + 45.f);
    auto endAngle = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants<float>::twoPi;
    
    auto range = getRange();
    
    auto valueToDraw = juce::jmap<float>(getValue(),
                                         range.getStart(),
                                         range.getEnd(),
                                         startAngle,
                                         endAngle);
    
    getLookAndFeel().drawRotarySlider(g,
                                      bounds.getCentreX() - radius, // x
                                      bounds.getCentreY() - radius, // y
                                      diameter,                     // width
                                      diameter,                     // height
                                      valueToDraw,                  // position
                                      startAngle,                   // start angle
                                      endAngle,                     // end angle
                                      *this);                       // slider
}
