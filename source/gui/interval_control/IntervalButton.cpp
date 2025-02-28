#include "IntervalButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
IntervalButton::IntervalButton(const Gui::Params::INTERVAL& interval)
    : CustomToggleButton(Gui::Params::getIntervalLabel(interval))
    , interval_(interval)
{
    setRadioGroupId(Gui::RADIO_GROUP_ID::INTERVAL_BUTTONS);
}

/*---------------------------------------------------------------------------
** End of File
*/
