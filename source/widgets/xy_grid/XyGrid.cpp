#include "XyGrid.h"

/*---------------------------------------------------------------------------
**
*/
XyGrid::XyGrid(PluginProcessor& processor_ref)
    : overlay_(processor_ref)
{
    addAndMakeVisible(canvas_);
    addAndMakeVisible(overlay_);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGrid::resized()
{
    const auto bounds = getLocalBounds();

    canvas_.setBounds(bounds.reduced(20));
    overlay_.setBounds(bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
