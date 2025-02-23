#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"
#include "IntervalButton.h"

class IntervalButtons : public juce::Component
{
public:
    IntervalButtons();

    void resized() override;

private:
    std::array< std::unique_ptr< IntervalButton >, IntervalParams::NUM_INTERVALS > buttons_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntervalButtons)
};
