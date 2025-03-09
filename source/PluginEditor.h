#pragma once

#include <JuceHeader.h>

#include "AnnotatedIntervalControl.h"
#include "CustomLookAndFeel.h"
#include "IntervalButtons.h"
#include "IntervalComboBox.h"
#include "PluginProcessor.h"
#include "RotaryGroup.h"
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

    RotaryGroup time_control_;
    RotaryGroup feedback_control_;
    RotaryGroup wet_control_;
    RotaryGroup dry_control_;

    XyGraph          xy_graph_;
    IntervalButtons  interval_buttons_;
    IntervalComboBox interval_combo_box_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
