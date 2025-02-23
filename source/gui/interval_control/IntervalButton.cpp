#include "IntervalButton.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
IntervalButton::IntervalButton(const IntervalParams::INTERVAL& interval)
    : CustomToggleButton(IntervalParams::getIntervalLabel(interval))
    , interval_(interval)
{
    setRadioGroupId(Gui::RADIO_GROUP_ID::INTERVAL_BUTTONS);
}

/*---------------------------------------------------------------------------
** End of File
*/
