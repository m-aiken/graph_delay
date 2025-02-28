#include "IntervalAnnotations.h"

/*---------------------------------------------------------------------------
**
*/
IntervalAnnotations::IntervalAnnotations()
{
    for (int i = 0; i < Gui::Params::NUM_INTERVALS; ++i) {
        const juce::String& str = Gui::Params::getIntervalLabel(static_cast< Gui::Params::INTERVAL >(i));
        labels_.at(i)           = std::make_unique< juce::Label >(str + "_label", str);

        addAndMakeVisible(labels_.at(i).get());
    }
}

/*---------------------------------------------------------------------------
**
*/
void
IntervalAnnotations::resized()
{
    const auto&   bounds      = getLocalBounds().toFloat();
    const auto    centre      = bounds.getCentre();
    constexpr int label_width = (Gui::LABEL_HEIGHT * 2);
    const auto    initial_label_bounds =
        juce::Rectangle< int >(centre.x - (label_width / 2), 0, label_width, Gui::LABEL_HEIGHT);

    for (int i = Gui::Params::FIRST_INTERVAL; i <= Gui::Params::LAST_INTERVAL; ++i) {
        const auto interval = static_cast< float >(i);
        const auto angle    = juce::jmap< float >(interval,
                                               Gui::Params::FIRST_INTERVAL,
                                               Gui::Params::LAST_INTERVAL,
                                               START_ANGLE,
                                               END_ANGLE);

        const auto& transformed_bounds = initial_label_bounds.transformedBy(
            juce::AffineTransform().rotated(angle, centre.x, centre.y));

        labels_.at(i)->setBounds(transformed_bounds);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
