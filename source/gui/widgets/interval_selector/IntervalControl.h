#pragma once

#include <JuceHeader.h>

#include "RotaryControl.h"

class IntervalControl : public RotaryControl
{
public:
    explicit IntervalControl(juce::AudioProcessorValueTreeState& apvts);

protected:
    [[nodiscard]] float getValueToDraw() const override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntervalControl)
};
