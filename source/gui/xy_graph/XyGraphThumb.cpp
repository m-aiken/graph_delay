#include "Theme.h"
#include "XyGraphThumb.h"

/*---------------------------------------------------------------------------
**
*/
void
XyGraphThumb::paint(juce::Graphics& g)
{
    g.setColour(Theme::getColour(Theme::SALMON));
    g.fillEllipse(getLocalBounds().toFloat());
}

/*---------------------------------------------------------------------------
** End of File
*/
