#include "RotaryControl.h"

/*---------------------------------------------------------------------------
**
*/
RotaryControl::RotaryControl(juce::AudioProcessorValueTreeState& apvts, const DelayParams::ParamId& param_id)
    : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , param_(apvts.getParameter(param_id))
{
    slider_attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment >(apvts, param_id, *this);

    if (param_ != nullptr) {
        param_->addListener(this);

        const juce::NormalisableRange< float >& range = param_->getNormalisableRange();

        setRange(range.start, range.end);
    }
}

/*---------------------------------------------------------------------------
**
*/
RotaryControl::~RotaryControl()
{
    if (param_ != nullptr) {
        param_->removeListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::paint(juce::Graphics& g)
{
    if (param_ == nullptr) {
        return;
    }

    const auto& bounds       = getLocalBounds();
    const auto  diameter     = static_cast< int >(std::floor(bounds.getWidth() * 0.9));
    const auto  radius       = static_cast< int >(std::floor(diameter * 0.5));
    const auto& range        = getRange();
    const auto value_to_draw = juce::jmap< double >(getValue(), range.getStart(), range.getEnd(), START_ANGLE, END_ANGLE);

    getLookAndFeel().drawRotarySlider(g,
                                      (bounds.getCentreX() - radius),
                                      (bounds.getCentreY() - radius),
                                      diameter,
                                      diameter,
                                      static_cast< float >(value_to_draw),
                                      START_ANGLE,
                                      END_ANGLE,
                                      *this);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::mouseEnter(const MouseEvent& event)
{
    juce::ignoreUnused(event);

    setMouseCursor(juce::MouseCursor::UpDownLeftRightResizeCursor);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::parameterValueChanged(int parameter_index, float new_value)
{
    juce::ignoreUnused(parameter_index, new_value);

    const juce::MessageManagerLock mml;

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryControl::parameterGestureChanged(int parameter_index, bool gesture_is_starting)
{
    // Only implemented because it's pure virtual.
    juce::ignoreUnused(parameter_index, gesture_is_starting);
}

/*---------------------------------------------------------------------------
** End of File
*/
