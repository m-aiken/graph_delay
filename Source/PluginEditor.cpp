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
    
    addAndMakeVisible(xyPad);
    
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
    g.fillAll (juce::Colours::black);
}

void JuceDelayV2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds       = getLocalBounds();
    auto width        = bounds.getWidth();
    auto bottom       = bounds.getBottom();
    auto padding      = 20;
    auto rotaryWidth  = 100;
    auto rotaryHeight = (bounds.getHeight() / 3);
    
    timeRotary.setBounds     (padding,                       padding * 2,                           rotaryWidth, rotaryHeight);
    feedbackRotary.setBounds (padding,                       bottom - (padding * 2) - rotaryHeight, rotaryWidth, rotaryHeight);
    dryRotary.setBounds      (width - rotaryWidth - padding, padding * 2,                           rotaryWidth, rotaryHeight);
    wetRotary.setBounds      (width - rotaryWidth - padding, bottom - (padding * 2) - rotaryHeight, rotaryWidth, rotaryHeight);
    
    auto xyPadDims = dryRotary.getX() - timeRotary.getRight() - (padding * 2);
    xyPad.setBounds(timeRotary.getRight() + padding, bounds.getCentreY() - (xyPadDims / 2), xyPadDims, xyPadDims);
}
