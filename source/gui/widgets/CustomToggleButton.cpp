#include "CustomToggleButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomToggleButton::CustomToggleButton(const juce::String& button_text)
    : juce::ToggleButton(button_text)
    , background_colour_(Theme::getColour(Theme::GREEN).withAlpha(0.1f))
{
}

/*---------------------------------------------------------------------------
**
*/
void
CustomToggleButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    const auto bounds = getLocalBounds();

    // Background.
    g.setColour(background_colour_);
    g.fillRoundedRectangle(bounds.toFloat(), BORDER_RADIUS);

    // Text.
    const auto& is_toggled = getToggleState();
    const auto& font       = Theme::getFont();

    g.setColour(Theme::getColour(Theme::BLUE).withAlpha(is_toggled ? 1.f : 0.4f));
    g.setFont(is_toggled ? font.boldened() : font);
    g.drawFittedText(getButtonText(), bounds, juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomToggleButton::mouseEnter(const juce::MouseEvent& event)
{
    juce::ignoreUnused(event);

    background_colour_ = Theme::getColour(Theme::GREEN).withAlpha(0.2f);

    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
CustomToggleButton::mouseExit(const juce::MouseEvent& event)
{
    juce::ignoreUnused(event);

    background_colour_ = Theme::getColour(Theme::GREEN).withAlpha(0.1f);

    repaint();
}

/*---------------------------------------------------------------------------
** End of File
*/
