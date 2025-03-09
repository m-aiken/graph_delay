#pragma once

#include <JuceHeader.h>

class RotaryShadow : public juce::Component
{
public:
    RotaryShadow();

    void paint(juce::Graphics& g) override;

private:
    static constexpr int SHADOW_RADIUS   = 24;
    static constexpr int SHADOW_DIAMETER = Gui::ROTARY_DIAMETER + SHADOW_RADIUS;

    juce::DropShadow shadow_;
    juce::Image      dummy_rotary_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryShadow)
};
