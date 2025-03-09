#include "GlobalConstants.h"
#include "RotaryShadow.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
RotaryShadow::RotaryShadow()
    : shadow_(Theme::getColour(Theme::SALMON), SHADOW_RADIUS, juce::Point< int >(0, 0))
    , dummy_rotary_(juce::Image::RGB, SHADOW_DIAMETER, SHADOW_DIAMETER, true)
{
    juce::Graphics g(dummy_rotary_);

    // Background.
    const juce::ColourGradient colour_gradient(Theme::getColour(Theme::SALMON),
                                               0,
                                               0,
                                               Theme::getColour(Theme::SALMON).withAlpha(0.3f),
                                               SHADOW_DIAMETER,
                                               SHADOW_DIAMETER,
                                               true);

    g.setGradientFill(colour_gradient);

    g.fillEllipse(SHADOW_RADIUS / 2, SHADOW_RADIUS / 2, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryShadow::paint(juce::Graphics& g)
{
    const auto& bounds              = getLocalBounds();
    const auto  shadow_image_radius = static_cast< int >(std::floor(SHADOW_DIAMETER * 0.5));
    const auto  image_x             = bounds.getCentreX() - shadow_image_radius;
    const auto  image_y             = bounds.getCentreY() - shadow_image_radius;
    const auto  image_bounds        = juce::Rectangle< int >(image_x, image_y, SHADOW_DIAMETER, SHADOW_DIAMETER);

    g.drawImage(dummy_rotary_, image_bounds.toFloat());

    shadow_.offset = juce::Point< int >(image_x, image_y);
    shadow_.drawForImage(g, dummy_rotary_);
}

/*---------------------------------------------------------------------------
** End of File
*/
