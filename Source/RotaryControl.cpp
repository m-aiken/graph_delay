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
    rotary.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    rotary.setRange(rangeMin, rangeMax);
    rotary.setNumDecimalPlacesToDisplay(2);
    
    addAndMakeVisible(label);
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
}

void RotaryControl::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void RotaryControl::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr (1));
    grid.templateRows = { Track(Fr (5)), Track(Fr (1)) };
    
    grid.items =
    {
        juce::GridItem(rotary),
        juce::GridItem(label)
    };
    
    grid.performLayout(getLocalBounds());
}
