#include "GlobalConstants.h"
#include "RotaryGroup.h"

/*---------------------------------------------------------------------------
**
*/
RotaryGroup::RotaryGroup(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id)
    : background_image_(
        juce::Drawable::createFromImageData(BinaryData::ellipse_blue_png, BinaryData::ellipse_blue_pngSize))
    , positon_marker_(apvts, param_id)
    , label_(param_id + "_label", param_id)
{
    addAndMakeVisible(positon_marker_);
    addAndMakeVisible(label_);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryGroup::paint(juce::Graphics& g)
{
    // g.setColour(juce::Colours::black);
    // g.drawRect(getLocalBounds(), 1);

    const auto&    og_bounds      = getLocalBounds().toFloat();
    constexpr auto image_diameter = 128.f;
    constexpr auto image_radius   = (image_diameter / 2);

    const auto image_bounds = juce::Rectangle< float >((og_bounds.getCentreX() - image_radius),
                                                       (og_bounds.getCentreY() - image_radius),
                                                       image_diameter,
                                                       image_diameter);

    background_image_.get()->drawWithin(g, image_bounds, juce::RectanglePlacement::centred, 1.f);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryGroup::resized()
{
    const auto& bounds = getLocalBounds();

    positon_marker_.centreWithSize(GraphDelay::ROTARY_DIAMETER, GraphDelay::ROTARY_DIAMETER);
    label_.setBounds(0, bounds.getBottom() - GraphDelay::LABEL_HEIGHT, bounds.getWidth(), GraphDelay::LABEL_HEIGHT);
}

/*---------------------------------------------------------------------------
**
*/
RotaryPositionMarker&
RotaryGroup::getPositionMarker()
{
    return positon_marker_;
}

/*---------------------------------------------------------------------------
** End of File
*/
