/*
  ==============================================================================

    XYPad.cpp
    Created: 7 Apr 2022 12:07:24am
    Author:  Matt Aiken

  ==============================================================================
*/

#include "XYPad.h"

//==============================================================================
void Thumb::paint(juce::Graphics& g)
{
    g.setColour(ColourMap::getColour(ColourMap::Salmon));
    g.fillEllipse(getLocalBounds().toFloat());
}

//==============================================================================
XYPad::XYPad()
{
    addAndMakeVisible(thumb);
}

void XYPad::paint(juce::Graphics& g)
{
    g.fillAll(ColourMap::getColour(ColourMap::Green).withAlpha(0.1f));
    g.drawImage(this->canvas, getLocalBounds().toFloat());
    
    auto thumbDiameter = 20;
    auto offsetCentre = getLocalBounds().getCentreX() - (thumbDiameter / 2);
    thumb.setBounds(offsetCentre, offsetCentre, thumbDiameter, thumbDiameter);
}

void XYPad::resized()
{
    auto bounds = getLocalBounds();
    canvas = juce::Image(juce::Image::RGB, bounds.getWidth(), bounds.getHeight(), true);
    
    juce::Graphics g(canvas);
    
    auto dot = bounds.getWidth() / 20;
    g.setColour(ColourMap::getColour(ColourMap::Blue).withAlpha(0.2f));
    for (auto x = 1; x < 20; ++x)
    {
        for (auto y = 1; y < 20; ++y)
        {
            g.drawRect((dot * x) - 1, (dot * y) - 1, 2, 2);
        }
        
    }
}
