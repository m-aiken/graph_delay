/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 8 Apr 2022 12:05:30am
    Author:  Matt Aiken

  ==============================================================================
*/

#include "CustomLookAndFeel.h"
#include "ColourMap.h"

//==============================================================================
void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                         int x, int y, int width, int height,
                                         float sliderPosProportional,
                                         float rotaryStartAngle,
                                         float rotaryEndAngle,
                                         juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, y, width, height);
    
    g.setColour(ColourMap::getColour(ColourMap::Salmon));
    g.fillEllipse(bounds);
    
    g.setColour(ColourMap::getColour(ColourMap::Blue));
    
    juce::Path p;
    
    auto centre = bounds.getCentre();
    
    juce::Rectangle<float> r;
    r.setLeft(centre.getX() - 3);
    r.setRight(centre.getX() + 3);
    r.setTop(bounds.getY() + 6);
    r.setBottom(bounds.getY() + 16);
    
    p.addRoundedRectangle(r, 2.f);
    
    jassert(rotaryStartAngle < rotaryEndAngle);
    
    auto transform = juce::AffineTransform().rotated(sliderPosProportional,
                                                     centre.getX(),
                                                     centre.getY());
    
    p.applyTransform(transform);
    
    g.fillPath(p);
}
