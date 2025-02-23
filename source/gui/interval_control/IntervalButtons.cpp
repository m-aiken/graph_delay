#include "IntervalButtons.h"

/*---------------------------------------------------------------------------
**
*/
IntervalButtons::IntervalButtons()
{
    for (size_t i = 0; i < IntervalParams::NUM_INTERVALS; ++i) {
        const auto interval = static_cast< IntervalParams::INTERVAL >(i);

        buttons_.at(i) = std::make_unique< IntervalButton >(interval);

        buttons_.at(i)->setToggleState(interval == IntervalParams::DEFAULT_INTERVAL, juce::dontSendNotification);

        addAndMakeVisible(buttons_.at(i).get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
IntervalButtons::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;
    using Px    = juce::Grid::Px;

    juce::Grid grid;

    grid.autoRows = Track(Fr(100));

    grid.templateColumns = {
        Track(Fr(1)),  //! 1/1
        Track(Fr(1)),  //! 1/2
        Track(Fr(1)),  //! 1/4
        Track(Fr(1)),  //! 1/8
        Track(Fr(1)),  //! 1/16
        Track(Fr(1)),  //! 1/32
        Track(Fr(1)),  //! 1/64
    };

    for (auto& button : buttons_) {
        grid.items.add(juce::GridItem(button.get()));
    }

    grid.setGap(Px(4));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
