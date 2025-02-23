#pragma once

#include <JuceHeader.h>

#include "CustomLabel.h"
#include "CustomLookAndFeel.h"
#include "IntervalButtons.h"
#include "PluginProcessor.h"
#include "RotaryControl.h"
#include "XyGraph.h"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor& p);
    ~PluginEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    PluginProcessor& processor_ref_;

    RotaryControl time_rotary_;
    RotaryControl feedback_rotary_;
    RotaryControl wet_rotary_;
    RotaryControl dry_rotary_;

    CustomLabel time_label_;
    CustomLabel feedback_label_;
    CustomLabel wet_label_;
    CustomLabel dry_label_;

    XyGraph xy_graph_;

    IntervalButtons interval_buttons_;

    CustomLookAndFeel lnf_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
