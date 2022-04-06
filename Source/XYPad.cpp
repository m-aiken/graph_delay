/*
  ==============================================================================

    XYPad.cpp
    Created: 7 Apr 2022 12:07:24am
    Author:  Matt Aiken

  ==============================================================================
*/

#include "XYPad.h"

//==============================================================================
void XYPad::paint(juce::Graphics& g)
{
//    g.fillAll(juce::Colours::darkgrey);
    g.drawImage(this->canvas, getLocalBounds().toFloat());
}

void XYPad::resized()
{
    auto bounds = getLocalBounds();
    canvas = juce::Image(juce::Image::RGB, bounds.getWidth(), bounds.getHeight(), true);
    
    juce::Graphics g(canvas);
    
    auto dot = bounds.getWidth() / 20;
    g.setColour(juce::Colours::lightblue.withAlpha(0.2f));
    for (auto x = 1; x < 20; ++x)
    {
        for (auto y = 1; y < 20; ++y)
        {
            g.drawRect((dot * x) - 1, (dot * y) - 1, 2, 2);
        }
        
    }
}
