/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceDelayV2AudioProcessorEditor::JuceDelayV2AudioProcessorEditor (JuceDelayV2AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      timeSliderAttachment(audioProcessor.apvts, "TIME", timeSlider),
      feedbackSliderAttachment(audioProcessor.apvts, "FEEDBACK", feedbackSlider),
      wetSliderAttachment(audioProcessor.apvts, "WET", wetSlider),
      drySliderAttachment(audioProcessor.apvts, "DRY", drySlider)
{
    addUIComponent(timeSlider, timeLabel, "Delay Time", "Rotary");
    addUIComponent(feedbackSlider, feedbackLabel, "Feedback", "Rotary");
    addUIComponent(wetSlider, wetLabel, "Wet", "LinearVertical");
    addUIComponent(drySlider, dryLabel, "Dry", "LinearVertical");
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
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
    
    auto container    = getLocalBounds();
    auto topTwenty    = container.removeFromTop(getHeight() * 0.2f);
    auto bottomTwenty = container.removeFromBottom(getHeight() * 0.2f);

    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid controls;

    controls.templateRows    = { Track(Fr (1)) };
    controls.templateColumns = { Track(Fr (3)), Track(Fr (3)), Track(Fr (1)), Track(Fr (1)) };

    auto timeS     = juce::GridItem(timeSlider);
    auto feedbackS = juce::GridItem(feedbackSlider);
    auto wetS      = juce::GridItem(wetSlider);
    auto dryS      = juce::GridItem(drySlider);

    timeS.margin     = 20;
    feedbackS.margin = 20;

    controls.items = { timeS, feedbackS, wetS, dryS };

    controls.performLayout(container);
}

void JuceDelayV2AudioProcessorEditor::addUIComponent(juce::Slider& slider,
                                                      juce::Label& label,
                                                      const juce::String& labelText,
                                                      const juce::String& sliderStyle)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(sliderStyle == "Rotary" ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    addAndMakeVisible(label);
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
}
