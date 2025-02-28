#include "AnnotatedIntervalControl.h"

/*---------------------------------------------------------------------------
**
*/
AnnotatedIntervalControl::AnnotatedIntervalControl(juce::AudioProcessorValueTreeState& apvts)
    : rotary_(apvts)
{
    addAndMakeVisible(rotary_);
    addAndMakeVisible(interval_annotations_);
}

/*---------------------------------------------------------------------------
**
*/
void
AnnotatedIntervalControl::resized()
{
    rotary_.centreWithSize(Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    interval_annotations_.setBounds(getLocalBounds());
}

/*---------------------------------------------------------------------------
** End of File
*/
