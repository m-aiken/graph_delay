#include "GlobalConstants.h"
#include "RotaryGroup.h"

/*---------------------------------------------------------------------------
**
*/
RotaryGroup::RotaryGroup(juce::AudioProcessorValueTreeState& apvts, const Gui::Params::ParamId& param_id)
    : rotary_(apvts, param_id)
    , label_(param_id + "_label", param_id)
{
    addAndMakeVisible(rotary_);
    addAndMakeVisible(shadow_);
    addAndMakeVisible(label_);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryGroup::resized()
{
    const auto& bounds = getLocalBounds();

    shadow_.setBounds(bounds);
    rotary_.centreWithSize(Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    label_.setBounds(0, bounds.getBottom() - Gui::LABEL_HEIGHT, bounds.getWidth(), Gui::LABEL_HEIGHT);
}

/*---------------------------------------------------------------------------
**
*/
RotaryControl&
RotaryGroup::getRotary()
{
    return rotary_;
}

/*---------------------------------------------------------------------------
** End of File
*/
