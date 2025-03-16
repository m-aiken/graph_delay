#include "GlobalConstants.h"
#include "RotaryControl.h"

/*---------------------------------------------------------------------------
**
*/
RotaryControl::RotaryControl(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id)
    : background_image_(
        juce::Drawable::createFromImageData(BinaryData::ellipse_blue_png, BinaryData::ellipse_blue_pngSize))
    , positon_marker_(apvts, param_id)
{
    addAndMakeVisible(positon_marker_);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::paint(juce::Graphics& g)
{
    background_image_->drawWithin(g, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, 1.f);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::resized()
{
    positon_marker_.centreWithSize(GraphDelay::ROTARY_DIAMETER, GraphDelay::ROTARY_DIAMETER);
}

/*---------------------------------------------------------------------------
** End of File
*/
