#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"
#include "RotaryControl.h"

class RotaryWithLabel : public juce::Component
{
public:
    RotaryWithLabel(juce::AudioProcessorValueTreeState& apvts, const DelayParams::ParamId& param_id);

    void resized() override;

    RotaryControl& getRotaryRef();

private:
    RotaryControl rotary_;
    juce::Label   label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryWithLabel)
};
