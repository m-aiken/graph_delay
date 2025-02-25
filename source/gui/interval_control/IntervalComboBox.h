#pragma once

#include <JuceHeader.h>

class IntervalComboBox : public juce::ComboBox
{
public:
    IntervalComboBox();

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntervalComboBox)
};
