#include "GlobalConstants.h"
#include "Theme.h"
#include "XyGraphCanvas.h"

/*---------------------------------------------------------------------------
**
*/
void
XyGraphCanvas::paint(juce::Graphics& g)
{
    // Background.
    g.fillAll(Theme::getColour(Theme::LIGHT_BLUE).withAlpha(0.15f));

    // Dots.
    g.setColour(Theme::getColour(Theme::DARK_BLUE).withAlpha(0.3f));

    const auto num_dots = getLocalBounds().getWidth() / GraphDelay::UI_MAGIC_NUMBER;

    for (auto x = 1; x < num_dots; ++x) {
        for (auto y = 1; y < num_dots; ++y) {
            g.drawRect((GraphDelay::UI_MAGIC_NUMBER * x) - 1, (GraphDelay::UI_MAGIC_NUMBER * y) - 1, 2, 2);
        }
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
