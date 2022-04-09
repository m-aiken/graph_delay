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
    
    addAndMakeVisible(timeLabel);
    addAndMakeVisible(feedbackLabel);
    addAndMakeVisible(wetLabel);
    addAndMakeVisible(dryLabel);
    
    formatLabel(timeLabel, "Time");
    formatLabel(feedbackLabel, "Feedback");
    formatLabel(wetLabel, "Wet");
    formatLabel(dryLabel, "Dry");
    
    addAndMakeVisible(xyPad);
    
    timeRotary.getValueObject().referTo     (audioProcessor.apvts.getParameterAsValue("TIME"));
    feedbackRotary.getValueObject().referTo (audioProcessor.apvts.getParameterAsValue("FEEDBACK"));
    wetRotary.getValueObject().referTo      (audioProcessor.apvts.getParameterAsValue("WET"));
    dryRotary.getValueObject().referTo      (audioProcessor.apvts.getParameterAsValue("DRY"));
    
    
    xyPad.getXValue().referTo               (audioProcessor.apvts.getParameterAsValue("TIME"));
    xyPad.getYValue().referTo               (audioProcessor.apvts.getParameterAsValue("FEEDBACK"));
    
    timeRotary.onValueChange     = [this] { xyPad.repaint(); };
    feedbackRotary.onValueChange = [this] { xyPad.repaint(); };
    
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
    g.fillAll(ColourMap::getColour(ColourMap::Eggshell));
}

void JuceDelayV2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds   = getLocalBounds();
    auto width    = bounds.getWidth();
    auto bottom   = bounds.getBottom();
    auto padding  = 20;
    auto rotaryXY = 100;
    auto labelHeight = rotaryXY / 4;
    
    timeRotary.setBounds     (padding,                    rotaryXY * 0.5,             rotaryXY, rotaryXY);
    feedbackRotary.setBounds (padding,                    bottom - (rotaryXY * 1.75), rotaryXY, rotaryXY);
    dryRotary.setBounds      (width - rotaryXY - padding, rotaryXY * 0.5,             rotaryXY, rotaryXY);
    wetRotary.setBounds      (width - rotaryXY - padding, bottom - (rotaryXY * 1.75), rotaryXY, rotaryXY);
    
    timeLabel.setBounds     (timeRotary.getX(),     timeRotary.getBottom(),     rotaryXY, labelHeight);
    feedbackLabel.setBounds (feedbackRotary.getX(), feedbackRotary.getBottom(), rotaryXY, labelHeight);
    wetLabel.setBounds      (wetRotary.getX(),      wetRotary.getBottom(),      rotaryXY, labelHeight);
    dryLabel.setBounds      (dryRotary.getX(),      dryRotary.getBottom(),      rotaryXY, labelHeight);
    
    auto xyPadDims = dryRotary.getX() - timeRotary.getRight() - (padding * 2);
    xyPad.setBounds(timeRotary.getRight() + padding, bounds.getCentreY() - (xyPadDims / 2), xyPadDims, xyPadDims);
}

void JuceDelayV2AudioProcessorEditor::formatLabel(juce::Label& label, const juce::String& labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 14.f, 0));
    label.setColour(juce::Label::ColourIds::textColourId, ColourMap::getColour(ColourMap::Blue));
}
