#include "GlobalConstants.h"
#include "IntervalComboBox.h"

/*---------------------------------------------------------------------------
**
*/
IntervalComboBox::IntervalComboBox()
    : juce::ComboBox("interval_combobox")
{
    for (int i = 0; i < IntervalParams::NUM_INTERVALS; ++i) {
        addItem(IntervalParams::getIntervalLabel(static_cast< IntervalParams::INTERVAL >(i)), (i + 1));
    }

    setSelectedId(IntervalParams::DEFAULT_INTERVAL + 1, juce::dontSendNotification);
}

/*---------------------------------------------------------------------------
**
*/
void
IntervalComboBox::paint(juce::Graphics& g)
{
    const auto& bounds = getLocalBounds();
    const auto  width  = bounds.getWidth();
    const auto  height = bounds.getHeight();

    getLookAndFeel().drawComboBox(g, width, height, false, 0, 0, width, height, *this);
}

/*---------------------------------------------------------------------------
** End of File
*/
