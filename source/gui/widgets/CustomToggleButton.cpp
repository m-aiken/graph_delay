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

    // Background.
    g.fillAll(background_colour_);

    // Outline.
    if (getToggleState()) {
        g.setColour(Theme::getColour(Theme::BLUE));
        g.drawRect(getLocalBounds(), 2);
    }

    // Text.
    g.setColour(Theme::getColour(Theme::BLUE));
    g.setFont(Theme::getFont());
    g.drawFittedText(getButtonText(), getLocalBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomToggleButton::mouseEnter(const juce::MouseEvent& event)
{
    juce::ignoreUnused(event);

    background_colour_ = Theme::getColour(Theme::GREEN).withAlpha(0.3f);

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
