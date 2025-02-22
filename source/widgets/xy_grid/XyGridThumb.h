#pragma once

#include <JuceHeader.h>

class XyGridThumb : public juce::Component
{
public:
    XyGridThumb() = default;

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGridThumb)
};
