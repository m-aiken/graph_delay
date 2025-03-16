#include "GlobalConstants.h"
#include "RotaryGroup.h"

/*---------------------------------------------------------------------------
**
*/
RotaryGroup::RotaryGroup(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id)
    : rotary_control_(apvts, param_id)
    , label_(param_id + "_label", param_id)
{
    addAndMakeVisible(rotary_control_);
    addAndMakeVisible(label_);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryGroup::resized()
{
    const auto& bounds = getLocalBounds();

    rotary_control_.setBounds(0, 0, GraphDelay::ROTARY_IMAGE_DIAMETER, GraphDelay::ROTARY_IMAGE_DIAMETER);
    label_.setBounds(0, bounds.getBottom() - GraphDelay::LABEL_HEIGHT, bounds.getWidth(), GraphDelay::LABEL_HEIGHT);
}

/*---------------------------------------------------------------------------
** End of File
*/
