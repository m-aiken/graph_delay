#pragma once

#include <JuceHeader.h>

class XyGridCanvas : public juce::Component
{
public:
    XyGridCanvas() = default;

    void paint(juce::Graphics& g) override;

private:
    enum { GRID_DIAMETER = 20 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGridCanvas)
};
