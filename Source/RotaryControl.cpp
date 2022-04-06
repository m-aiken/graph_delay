/*
  ==============================================================================

    RotaryControl.cpp
    Created: 6 Apr 2022 11:23:20pm
    Author:  Matt Aiken

  ==============================================================================
*/

#include "RotaryControl.h"

//==============================================================================
RotaryControl::RotaryControl(const juce::String& labelText, const double& rangeMin, const double& rangeMax)
{
    addAndMakeVisible(rotary);
    rotary.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    rotary.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    rotary.setRange(rangeMin, rangeMax);
    
    addAndMakeVisible(label);
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 14.f, 0));
}

void RotaryControl::paint(juce::Graphics& g)
{
//    g.fillAll(juce::Colours::blue);
}

void RotaryControl::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr (1));
    grid.templateRows = { Track(Fr (4)), Track(Fr (1)) };
    
    grid.items =
    {
        juce::GridItem(rotary),
        juce::GridItem(label)
    };
    
    grid.performLayout(getLocalBounds());
}
