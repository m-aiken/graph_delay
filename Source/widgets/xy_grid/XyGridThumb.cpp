#include "Theme.h"
#include "XyGridThumb.h"

/*---------------------------------------------------------------------------
**
*/
void
XyGridThumb::paint(juce::Graphics& g)
{
    g.setColour(Theme::getColour(Theme::SALMON));
    g.fillEllipse(getLocalBounds().toFloat());
}

/*---------------------------------------------------------------------------
** End of File
*/
