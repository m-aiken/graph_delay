#pragma once

#include <JuceHeader.h>

#include "CustomLookAndFeel.h"
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
    PluginProcessor&  processor_ref_;
    CustomLookAndFeel lnf_;

    XyGraph     xy_graph_;
    RotaryGroup wet_control_;
    RotaryGroup dry_control_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
