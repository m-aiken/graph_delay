#include "Theme.h"
#include "XyGraphCanvas.h"

/*---------------------------------------------------------------------------
**
*/
void
XyGraphCanvas::paint(juce::Graphics& g)
{
    // Background.
    g.fillAll(Theme::getColour(Theme::GREEN).withAlpha(0.1f));

    // Dots.
    g.setColour(Theme::getColour(Theme::BLUE).withAlpha(0.2f));

    const auto increment = getLocalBounds().getWidth() / GRID_DIAMETER;

    for (auto x = 1; x < GRID_DIAMETER; ++x) {
        for (auto y = 1; y < GRID_DIAMETER; ++y) {
            g.drawRect((increment * x) - 1, (increment * y) - 1, 2, 2);
        }
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
