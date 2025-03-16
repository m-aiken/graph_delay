#pragma once

#include <JuceHeader.h>

#include "RotaryControl.h"
#include "RotaryPositionMarker.h"

class RotaryGroup : public juce::Component
{
public:
    RotaryGroup(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id);

    void resized() override;

private:
    RotaryControl rotary_control_;
    juce::Label   label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryGroup)
};
