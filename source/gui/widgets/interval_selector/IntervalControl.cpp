#include "GlobalConstants.h"
#include "IntervalControl.h"

/*---------------------------------------------------------------------------
**
*/
IntervalControl::IntervalControl(juce::AudioProcessorValueTreeState& apvts)
    : RotaryControl(apvts, Gui::Params::DISCRETE_TIME)
{
}

/*---------------------------------------------------------------------------
**
*/
float
IntervalControl::getValueToDraw() const
{
    if (param_ == nullptr) {
        return START_ANGLE;
    }

    const auto& interval = static_cast< Gui::Params::INTERVAL >(param_->convertFrom0to1(param_->getValue()));

    return juce::jmap< float >(interval, Gui::Params::FIRST_INTERVAL, Gui::Params::LAST_INTERVAL, START_ANGLE, END_ANGLE);
}

/*---------------------------------------------------------------------------
** End of File
*/
