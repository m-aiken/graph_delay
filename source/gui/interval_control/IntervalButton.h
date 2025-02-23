#pragma once

#include <JuceHeader.h>

#include "CustomToggleButton.h"
#include "GlobalConstants.h"

class IntervalButton : public CustomToggleButton
{
public:
    explicit IntervalButton(const IntervalParams::INTERVAL& interval);

private:
    const IntervalParams::INTERVAL interval_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntervalButton)
};
