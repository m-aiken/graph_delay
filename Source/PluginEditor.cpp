/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceDelayV2AudioProcessorEditor::JuceDelayV2AudioProcessorEditor (JuceDelayV2AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    addAndMakeVisible(timeRotary);
    addAndMakeVisible(feedbackRotary);
    addAndMakeVisible(wetRotary);
    addAndMakeVisible(dryRotary);
    
    timeRotary.getValueObject().referTo     (audioProcessor.apvts.getParameterAsValue("TIME"));
    feedbackRotary.getValueObject().referTo (audioProcessor.apvts.getParameterAsValue("FEEDBACK"));
    wetRotary.getValueObject().referTo      (audioProcessor.apvts.getParameterAsValue("WET"));
    dryRotary.getValueObject().referTo      (audioProcessor.apvts.getParameterAsValue("DRY"));
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

JuceDelayV2AudioProcessorEditor::~JuceDelayV2AudioProcessorEditor()
{
}

//==============================================================================
void JuceDelayV2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::red);
}

void JuceDelayV2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds      = getLocalBounds();
    int rotaryWidth  = 100;
    int rotaryHeight = bounds.getHeight() / 2;
    
    timeRotary.setBounds     (0,                               0,            rotaryWidth, rotaryHeight);
    feedbackRotary.setBounds (0,                               rotaryHeight, rotaryWidth, rotaryHeight);
    dryRotary.setBounds      (bounds.getWidth() - rotaryWidth, 0,            rotaryWidth, rotaryHeight);
    wetRotary.setBounds      (bounds.getWidth() - rotaryWidth, rotaryHeight, rotaryWidth, rotaryHeight);
}
