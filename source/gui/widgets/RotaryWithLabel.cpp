#include "RotaryWithLabel.h"

/*---------------------------------------------------------------------------
**
*/
RotaryWithLabel::RotaryWithLabel(juce::AudioProcessorValueTreeState& apvts, const DelayParams::ParamId& param_id)
    : rotary_(apvts, param_id)
    , label_(param_id + "_label", param_id)
{
    addAndMakeVisible(rotary_);
    addAndMakeVisible(label_);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryWithLabel::resized()
{
    using Track = juce::Grid::TrackInfo;
    using Fr    = juce::Grid::Fr;

    juce::Grid grid;

    grid.autoColumns = Track(Fr(100));

    grid.templateRows = {
        Track(Fr(80)),  //! Rotary.
        Track(Fr(20)),  //! Label.
    };

    grid.items.add(juce::GridItem(rotary_));
    grid.items.add(juce::GridItem(label_));

    grid.performLayout(getLocalBounds());
}

/*---------------------------------------------------------------------------
**
*/
RotaryControl&
RotaryWithLabel::getRotaryRef()
{
    return rotary_;
}

/*---------------------------------------------------------------------------
** End of File
*/
