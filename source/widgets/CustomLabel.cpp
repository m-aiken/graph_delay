#include "CustomLabel.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
CustomLabel::CustomLabel(const DelayParams::ParamId& param_id)
    : juce::Label(param_id + "_label", param_id)
{
    setJustificationType(juce::Justification::centred);
    setFont(Theme::getFont());
    setColour(juce::Label::ColourIds::textColourId, Theme::getColour(Theme::BLUE));
}

/*---------------------------------------------------------------------------
** End of File
*/
