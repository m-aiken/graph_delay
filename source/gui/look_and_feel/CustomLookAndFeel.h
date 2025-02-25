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

    // juce::ComboBox
    void drawComboBox(juce::Graphics& g,
                      int             width,
                      int             height,
                      bool            is_button_down,
                      int             button_x,
                      int             button_y,
                      int             button_w,
                      int             button_h,
                      juce::ComboBox& combo_box) override;

    juce::Label* createComboBoxTextBox(juce::ComboBox& combo_box) override;

    void positionComboBoxText(juce::ComboBox& combo_box, juce::Label& label_to_position) override;

    // juce::Label
    void drawLabel(juce::Graphics& g, juce::Label& label) override;

    // juce::PopupMenu
    void drawPopupMenuBackgroundWithOptions(juce::Graphics&                 g,
                                            int                             width,
                                            int                             height,
                                            const juce::PopupMenu::Options& options) override;

    void drawPopupMenuItemWithOptions(juce::Graphics&                 g,
                                      const juce::Rectangle< int >&   area,
                                      bool                            is_highlighted,
                                      const juce::PopupMenu::Item&    item,
                                      const juce::PopupMenu::Options& options) override;

    int getPopupMenuBorderSize() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
