#pragma once

#include <JuceHeader.h>

class CustomToggleButton : public juce::ToggleButton
{
public:
    explicit CustomToggleButton(const juce::String& button_text);

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;
    void mouseEnter(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;

private:
    juce::Colour background_colour_;

    static constexpr uint8 BORDER_RADIUS = 8;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomToggleButton)
};
