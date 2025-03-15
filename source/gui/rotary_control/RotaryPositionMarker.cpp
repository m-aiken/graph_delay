#include "RotaryPositionMarker.h"

/*---------------------------------------------------------------------------
**
*/
RotaryPositionMarker::RotaryPositionMarker(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id)
    : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , param_(apvts.getParameter(param_id))
{
    slider_attachment_ = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment >(apvts, param_id, *this);

    if (param_ != nullptr) {
        param_->addListener(this);

        const juce::NormalisableRange< float >& range = param_->getNormalisableRange();

        setRange(range.start, range.end);
    }

    setAlwaysOnTop(true);
}

/*---------------------------------------------------------------------------
**
*/
RotaryPositionMarker::~RotaryPositionMarker()
{
    if (param_ != nullptr) {
        param_->removeListener(this);
    }
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryPositionMarker::paint(juce::Graphics& g)
{
    const auto& bounds = getLocalBounds();

    getLookAndFeel()
        .drawRotarySlider(g, 0, 0, bounds.getWidth(), bounds.getHeight(), getValueToDraw(), START_ANGLE, END_ANGLE, *this);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryPositionMarker::mouseEnter(const juce::MouseEvent& event)
{
    setMouseCursor(juce::MouseCursor::UpDownLeftRightResizeCursor);

    juce::Slider::mouseEnter(event);
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryPositionMarker::parameterValueChanged(int parameter_index, float new_value)
{
    juce::ignoreUnused(parameter_index, new_value);

    const juce::MessageManagerLock mml;

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
void
RotaryPositionMarker::parameterGestureChanged(int parameter_index, bool gesture_is_starting)
{
    // Only implemented because it's pure virtual.
    juce::ignoreUnused(parameter_index, gesture_is_starting);
}

/*---------------------------------------------------------------------------
**
*/
float
RotaryPositionMarker::getValueToDraw() const
{
    if (param_ == nullptr) {
        return START_ANGLE;
    }

    const auto& range = getRange();

    return juce::jmap< float >(static_cast< float >(getValue()), range.getStart(), range.getEnd(), START_ANGLE, END_ANGLE);
}

/*---------------------------------------------------------------------------
** End of File
*/
