#pragma once

#include <JuceHeader.h>

class XyGraphCanvas : public juce::Component
{
public:
    XyGraphCanvas() = default;

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGraphCanvas)
};
