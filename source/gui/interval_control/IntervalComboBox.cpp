#include "GlobalConstants.h"
#include "IntervalComboBox.h"

/*---------------------------------------------------------------------------
**
*/
IntervalComboBox::IntervalComboBox()
    : juce::ComboBox("interval_combobox")
{
    for (int i = 0; i < Gui::Params::NUM_INTERVALS; ++i) {
        addItem(Gui::Params::getIntervalLabel(static_cast< Gui::Params::INTERVAL >(i)), (i + 1));
    }

    setSelectedId(Gui::Params::DEFAULT_INTERVAL + 1, juce::dontSendNotification);
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
