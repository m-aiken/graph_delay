#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel() = default;

    // juce::Slider
    void drawRotarySlider(juce::Graphics& g,
                          int             x,
                          int             y,
                          int             width,
                          int             height,
                          float           slider_pos_proportional,
                          float           rotary_start_angle,
                          float           rotary_end_angle,
                          juce::Slider&   slider) override;

    // juce::Label
    void drawLabel(juce::Graphics& g, juce::Label& label) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
