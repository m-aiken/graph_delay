#include "Theme.h"
#include "XyGraph.h"

/*---------------------------------------------------------------------------
**
*/
XyGraph::XyGraph(PluginProcessor& processor_ref)
    : processor_ref_(processor_ref)
    , thumb_shadow_(Theme::getColour(Theme::DARK_BLUE).withAlpha(0.2f), SHADOW_RADIUS, juce::Point< int >(2, 2))
    , overlay_(processor_ref)
{
    addAndMakeVisible(canvas_);
    addAndMakeVisible(thumb_);
    addAndMakeVisible(overlay_);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraph::paint(juce::Graphics& g)
{
    const auto thumb_bounds = juce::Rectangle< int >(getXCoordinateFromParameterValue() + THUMB_RADIUS,
                                                     getYCoordinateFromParameterValue() + THUMB_RADIUS,
                                                     GraphDelay::THUMB_DIAMETER,
                                                     GraphDelay::THUMB_DIAMETER);

    thumb_.setBounds(thumb_bounds);
    thumb_shadow_.drawForRectangle(g, thumb_bounds);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraph::resized()
{
    const auto bounds = getLocalBounds();

    canvas_.setBounds(bounds.reduced(GraphDelay::UI_MAGIC_NUMBER));
    overlay_.setBounds(bounds);
}

/*---------------------------------------------------------------------------
**
*/
int
XyGraph::getXCoordinateFromParameterValue() const
{
    const float source_value = processor_ref_.getParamValue(GraphDelay::TIME);
    const float target_max   = getLocalBounds().reduced(GraphDelay::THUMB_DIAMETER).toFloat().getWidth();
    const auto  coordinate =
        juce::jmap< float >(source_value, GraphDelay::DELAY_MS_MIN, GraphDelay::DELAY_MS_MAX, 0, target_max);

    return static_cast< int >(std::floor(coordinate));
}

/*---------------------------------------------------------------------------
**
*/
int
XyGraph::getYCoordinateFromParameterValue() const
{
    const float source_value = processor_ref_.getParamValue(GraphDelay::FEEDBACK);
    const float target_min   = getLocalBounds().reduced(GraphDelay::THUMB_DIAMETER).toFloat().getHeight();
    const auto  coordinate =
        juce::jmap< float >(source_value, GraphDelay::FEEDBACK_MIN, GraphDelay::FEEDBACK_MAX, target_min, 0);

    return static_cast< int >(std::floor(coordinate));
}

/*---------------------------------------------------------------------------
** End of File
*/
