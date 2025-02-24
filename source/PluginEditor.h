#pragma once

#include <JuceHeader.h>

#include "CustomLookAndFeel.h"
#include "IntervalButtons.h"
#include "PluginProcessor.h"
#include "RotaryWithLabel.h"
#include "XyGraph.h"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor& p);
    ~PluginEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    PluginProcessor&  processor_ref_;
    CustomLookAndFeel lnf_;

    RotaryWithLabel time_rotary_;
    RotaryWithLabel feedback_rotary_;
    RotaryWithLabel wet_rotary_;
    RotaryWithLabel dry_rotary_;
    XyGraph         xy_graph_;
    IntervalButtons interval_buttons_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
