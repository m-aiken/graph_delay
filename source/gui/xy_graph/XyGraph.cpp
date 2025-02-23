#include "XyGraph.h"

/*---------------------------------------------------------------------------
**
*/
XyGraph::XyGraph(PluginProcessor& processor_ref)
    : overlay_(processor_ref)
{
    addAndMakeVisible(canvas_);
    addAndMakeVisible(overlay_);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraph::resized()
{
    const auto bounds = getLocalBounds();

    canvas_.setBounds(bounds.reduced(20));
    overlay_.setBounds(bounds);
}

/*---------------------------------------------------------------------------
** End of File
*/
