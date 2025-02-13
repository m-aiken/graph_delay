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
** End of File
*/
