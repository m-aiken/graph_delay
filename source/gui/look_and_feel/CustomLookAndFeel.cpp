#include "CustomLookAndFeel.h"
#include "Theme.h"

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

    // The background is transparent.
    // Because the drawing of the rotary shadow is expensive, we draw a static image
    // as the rotary background and then draw the position pointer over it dynamically.

    // Position marker.
    juce::Rectangle< float > thumb;
    juce::Path               path;
    const auto               centre = bounds.getCentre();

    thumb.setLeft(centre.getX() - 3);
    thumb.setRight(centre.getX() + 3);
    thumb.setTop(bounds.getY() + 6);
    thumb.setBottom(bounds.getY() + 12);

    path.addRoundedRectangle(thumb, 2.f);
    path.applyTransform(juce::AffineTransform().rotated(slider_pos_proportional, centre.getX(), centre.getY()));

    g.setColour(Theme::getColour(Theme::EGGSHELL).withAlpha(0.6f));
    g.fillPath(path);
}

/*---------------------------------------------------------------------------
**
*/
void
CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.setColour(Theme::getColour(Theme::DARK_BLUE));
    g.setFont(Theme::getFont());
    g.drawFittedText(label.getText(), g.getClipBounds(), juce::Justification::centred, 1);
}

/*---------------------------------------------------------------------------
** End of File
*/
