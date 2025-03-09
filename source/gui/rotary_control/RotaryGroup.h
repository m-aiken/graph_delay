#pragma once

#include <JuceHeader.h>

#include "RotaryControl.h"
#include "RotaryShadow.h"

class RotaryGroup : public juce::Component
{
public:
    RotaryGroup(juce::AudioProcessorValueTreeState& apvts, const Gui::Params::ParamId& param_id);

    void resized() override;

    RotaryControl& getRotary();

private:
    RotaryControl rotary_;
    RotaryShadow  shadow_;
    juce::Label   label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryGroup)
};
