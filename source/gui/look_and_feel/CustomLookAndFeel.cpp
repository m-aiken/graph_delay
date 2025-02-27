#include "CustomLookAndFeel.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomLookAndFeel::CustomLookAndFeel()
{
    setColour(juce::PopupMenu::backgroundColourId, juce::Colours::white.withAlpha(0.f));  // Completely transparent.
}

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                    int             x,
                                    int             y,
                                    int             width,
                                    int             height,
                                    float           slider_pos_proportional,
                                    float           rotary_start_angle,
                                    float           rotary_end_angle,
                                    juce::Slider&   slider)
{
    const auto bounds = juce::Rectangle< int >(x, y, width, height).toFloat();

    // Background.
    g.setColour(Theme::getColour(Theme::SALMON));
    g.fillEllipse(bounds);

    // Thumb/Pointer.
    juce::Rectangle< float > thumb;
    juce::Path               path;
    const auto               centre = bounds.getCentre();

    thumb.setLeft(centre.getX() - 3);
    thumb.setRight(centre.getX() + 3);
    thumb.setTop(bounds.getY() + 6);
    thumb.setBottom(bounds.getY() + 16);

    path.addRoundedRectangle(thumb, 2.f);
    path.applyTransform(juce::AffineTransform().rotated(slider_pos_proportional, centre.getX(), centre.getY()));

    g.setColour(Theme::getColour(Theme::BLUE));
    g.fillPath(path);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawComboBox(juce::Graphics& g,
                                int             width,
                                int             height,
                                bool            is_button_down,
                                int             button_x,
                                int             button_y,
                                int             button_w,
                                int             button_h,
                                juce::ComboBox& combo_box)
{
    // Background.
    g.fillAll(Theme::getColour(Theme::GREEN).withAlpha(0.1f));

    juce::String text = combo_box.getText();

    if (text.isEmpty()) {
        text = combo_box.getTextWhenNothingSelected();
    }

    g.drawFittedText(text, combo_box.getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
juce::Label*
CustomLookAndFeel::createComboBoxTextBox(juce::ComboBox& combo_box)
{
    auto* label = new juce::Label();

    label->setFont(Theme::getFont());
    label->setJustificationType(juce::Justification::centred);
    label->setEditable(false);

    return label;
}

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::positionComboBoxText(juce::ComboBox& combo_box, juce::Label& label_to_position)
{
    label_to_position.setBounds(combo_box.getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
juce::PopupMenu::Options
CustomLookAndFeel::getOptionsForComboBoxPopupMenu(juce::ComboBox& combo_box, juce::Label& label)
{
    return PopupMenu::Options().withTargetComponent(combo_box);
}

/*---------------------------------------------------------------------------
**
*/
juce::Font
CustomLookAndFeel::getComboBoxFont(juce::ComboBox& combo_box)
{
    return Theme::getFont();
}

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.setColour(Theme::getColour(Theme::BLUE));
    g.setFont(Theme::getFont());
    g.drawFittedText(label.getText(), g.getClipBounds(), juce::Justification::centred, 1);
}
#if 0
/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawPopupMenuBackgroundWithOptions(juce::Graphics&                 g,
                                                      int                             width,
                                                      int                             height,
                                                      const juce::PopupMenu::Options& options)
{
}
#endif

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawPopupMenuItemWithOptions(juce::Graphics&                 g,
                                                const juce::Rectangle< int >&   area,
                                                bool                            is_highlighted,
                                                const juce::PopupMenu::Item&    item,
                                                const juce::PopupMenu::Options& options)
{
    const float alpha = is_highlighted ? 0.1f : 0.05f;

    // Background.
    g.fillAll(Theme::getColour(Theme::GREEN).withAlpha(alpha));

    // Text.
    g.setFont(Theme::getFont());
    g.setColour(Theme::getColour(Theme::BLUE));
    g.drawFittedText(item.text, area, juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
int
CustomLookAndFeel::getPopupMenuBorderSize()
{
    return 0;
}

/*---------------------------------------------------------------------------
**
*/
juce::Font
CustomLookAndFeel::getPopupMenuFont()
{
    return Theme::getFont();
}

/*---------------------------------------------------------------------------
**
*/
juce::Component*
CustomLookAndFeel::getParentComponentForMenuOptions(const juce::PopupMenu::Options& options)
{
    if (auto* comp = options.getParentComponent()) {
        return comp;
    }

    if (auto* target_comp = options.getTargetComponent()) {
        if (auto* editor = target_comp->findParentComponentOfClass< AudioProcessorEditor >()) {
            return editor;
        }
    }

    return LookAndFeel_V4::getParentComponentForMenuOptions(options);
}

/*---------------------------------------------------------------------------
** End of File
*/
