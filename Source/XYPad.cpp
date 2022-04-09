/*
  ==============================================================================

    XYPad.cpp
    Created: 7 Apr 2022 12:07:24am
    Author:  Matt Aiken

  ==============================================================================
*/

#include "XYPad.h"

//==============================================================================
void Canvas::paint(juce::Graphics& g)
{
    g.fillAll(ColourMap::getColour(ColourMap::Green).withAlpha(0.1f));
    
    auto matrixDims = 20;
    auto coord = getLocalBounds().getWidth() / matrixDims;
    g.setColour(ColourMap::getColour(ColourMap::Blue).withAlpha(0.2f));
    for (auto x = 1; x < matrixDims; ++x)
    {
        for (auto y = 1; y < matrixDims; ++y)
        {
            g.drawRect((coord * x) - 1, (coord * y) - 1, 2, 2);
        }
    }
}

//==============================================================================
void Thumb::paint(juce::Graphics& g)
{
    g.setColour(ColourMap::getColour(ColourMap::Salmon));
    g.fillEllipse(getLocalBounds().toFloat());
}

//==============================================================================
Overlay::Overlay()
{
    addAndMakeVisible(thumb);
}

void Overlay::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    setBounds(bounds);
    
    auto xScaled = juce::jmap<float>(xValue.getValue(), 0.f, 1000.f, 0, bounds.getWidth());
    auto yScaled = juce::jmap<float>(yValue.getValue(), 0.f, 1.f, bounds.getHeight(), 0);
    
    auto thumbDiameter = 20;
    auto thumbBounds = juce::Rectangle<int>(std::floor(xScaled) - (thumbDiameter / 2),
                                            std::floor(yScaled) - (thumbDiameter / 2),
                                            thumbDiameter,
                                            thumbDiameter);
    thumb.setBounds(thumbBounds);
    
    auto shadow = juce::DropShadow(ColourMap::getColour(ColourMap::Salmon), 20, juce::Point<int>(0, 0));
    shadow.drawForRectangle(g, thumbBounds);
}

void Overlay::mouseDrag(const juce::MouseEvent& event)
{
    auto bounds = getLocalBounds();
    
    auto xScaled = juce::jmap<float>(event.getPosition().getX(), 0, bounds.getWidth(), 0.f, 1000.f);
    auto yScaled = juce::jmap<float>(event.getPosition().getY(), 0, bounds.getHeight(), 1.f, 0.f);
    
    xValue.setValue(juce::jlimit<float>(0.f, 1000.f, xScaled));
    yValue.setValue(juce::jlimit<float>(0.f, 1.f, yScaled));
    
    repaint();
}

//==============================================================================
XYContainer::XYContainer()
{
    addAndMakeVisible(canvas);
    addAndMakeVisible(overlay);
}

void XYContainer::resized()
{
    auto bounds = getLocalBounds();
    canvas.setBounds(bounds);
    overlay.setBounds(bounds);
}
