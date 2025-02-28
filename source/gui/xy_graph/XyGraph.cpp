#include "Theme.h"
#include "XyGraph.h"

/*---------------------------------------------------------------------------
**
*/
XyGraph::XyGraph(PluginProcessor& processor_ref)
    : processor_ref_(processor_ref)
    , thumb_shadow_(Theme::getColour(Theme::SALMON).withAlpha(0.6f), SHADOW_RADIUS, juce::Point< int >(0, 0))
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
                                                     Gui::THUMB_DIAMETER,
                                                     Gui::THUMB_DIAMETER);

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

    canvas_.setBounds(bounds.reduced(Gui::UI_MULTIPLE));
    overlay_.setBounds(bounds);
}

/*---------------------------------------------------------------------------
**
*/
int
XyGraph::getXCoordinateFromParameterValue() const
{
    const float source_value = processor_ref_.getParamValue(Gui::Params::TIME);
    const float target_max   = getLocalBounds().reduced(Gui::THUMB_DIAMETER).toFloat().getWidth();
    const auto  coordinate =
        juce::jmap< float >(source_value, Gui::Params::DELAY_MS_MIN, Gui::Params::DELAY_MS_MAX, 0, target_max);

    return static_cast< int >(std::floor(coordinate));
}

/*---------------------------------------------------------------------------
**
*/
int
XyGraph::getYCoordinateFromParameterValue() const
{
    const float source_value = processor_ref_.getParamValue(Gui::Params::FEEDBACK);
    const float target_min   = getLocalBounds().reduced(Gui::THUMB_DIAMETER).toFloat().getHeight();
    const auto  coordinate =
        juce::jmap< float >(source_value, Gui::Params::FEEDBACK_MIN, Gui::Params::FEEDBACK_MAX, target_min, 0);

    return static_cast< int >(std::floor(coordinate));
}

/*---------------------------------------------------------------------------
** End of File
*/
