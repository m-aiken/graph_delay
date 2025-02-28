#pragma once

#include <JuceHeader.h>

#include "AnnotatedIntervalControl.h"
#include "CustomLookAndFeel.h"
#include "IntervalButtons.h"
#include "IntervalComboBox.h"
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
    [[nodiscard]] static juce::Rectangle< int > getRotaryLabelBounds(const RotaryControl& rotary_to_annotate);

    PluginProcessor&  processor_ref_;
    CustomLookAndFeel lnf_;

    AnnotatedIntervalControl discrete_time_rotary_;

    RotaryControl time_rotary_;
    juce::Label   time_label_;
    RotaryControl feedback_rotary_;
    juce::Label   feedback_label_;
    RotaryControl wet_rotary_;
    juce::Label   wet_label_;
    RotaryControl dry_rotary_;
    juce::Label   dry_label_;

    XyGraph          xy_graph_;
    IntervalButtons  interval_buttons_;
    IntervalComboBox interval_combo_box_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
