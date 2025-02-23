#pragma once

#include <JuceHeader.h>

class XyGraphThumb : public juce::Component
{
public:
    XyGraphThumb() = default;

    void paint(juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGraphThumb)
};
