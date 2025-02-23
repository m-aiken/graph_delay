#include "GlobalConstants.h"
#include "Theme.h"
#include "XyGraphOverlay.h"

/*---------------------------------------------------------------------------
**
*/
XyGraphOverlay::XyGraphOverlay(PluginProcessor& processor_ref)
    : processor_ref_(processor_ref)
    , thumb_shadow_(Theme::getColour(Theme::SALMON).withAlpha(0.6f), SHADOW_RADIUS, juce::Point< int >(0, 0))
{
    addAndMakeVisible(thumb_);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraphOverlay::paint(juce::Graphics& g)
{
    const auto thumb_bounds = juce::Rectangle< int >(getXCoordinateFromParameterValue() + THUMB_RADIUS,
                                                     getYCoordinateFromParameterValue() + THUMB_RADIUS,
                                                     THUMB_DIAMETER,
                                                     THUMB_DIAMETER);

    thumb_.setBounds(thumb_bounds);
    thumb_shadow_.drawForRectangle(g, thumb_bounds);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraphOverlay::mouseDrag(const juce::MouseEvent& event)
{
    juce::RangedAudioParameter* time_param     = processor_ref_.getApvts().getParameter(DelayParams::TIME);
    juce::RangedAudioParameter* feedback_param = processor_ref_.getApvts().getParameter(DelayParams::FEEDBACK);

    if (time_param != nullptr && feedback_param != nullptr) {
        const float time     = getParameterValueFromXCoordinate(event.getPosition().getX());
        const float feedback = getParameterValueFromYCoordinate(event.getPosition().getY());

        time_param->beginChangeGesture();
        time_param->setValueNotifyingHost(time_param->convertTo0to1(time));
        time_param->endChangeGesture();

        feedback_param->beginChangeGesture();
        feedback_param->setValueNotifyingHost(feedback_param->convertTo0to1(feedback));
        feedback_param->endChangeGesture();
    }

    repaint();
}

/*---------------------------------------------------------------------------
**
*/
int
XyGraphOverlay::getXCoordinateFromParameterValue() const
{
    const float source_value = processor_ref_.getParamValue(DelayParams::TIME);
    const float target_max   = getLocalBounds().reduced(THUMB_DIAMETER).toFloat().getWidth();
    const auto  coordinate =
        juce::jmap< float >(source_value, DelayParams::DELAY_MS_MIN, DelayParams::DELAY_MS_MAX, 0, target_max);

    return static_cast< int >(std::floor(coordinate));
}

/*---------------------------------------------------------------------------
**
*/
int
XyGraphOverlay::getYCoordinateFromParameterValue() const
{
    const float source_value = processor_ref_.getParamValue(DelayParams::FEEDBACK);
    const float target_min   = getLocalBounds().reduced(THUMB_DIAMETER).toFloat().getHeight();
    const auto  coordinate =
        juce::jmap< float >(source_value, DelayParams::FEEDBACK_MIN, DelayParams::FEEDBACK_MAX, target_min, 0);

    return static_cast< int >(std::floor(coordinate));
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
XyGraphOverlay::getParameterValueFromXCoordinate(int x_coordinate)
{
    x_coordinate = juce::jlimit< int >(MIN_VALID_COORDINATE, MAX_VALID_COORDINATE, x_coordinate);

    const auto parameter_value = juce::jmap< float >(static_cast< float >(x_coordinate),
                                                     static_cast< float >(MIN_VALID_COORDINATE),
                                                     static_cast< float >(MAX_VALID_COORDINATE),
                                                     DelayParams::DELAY_MS_MIN,
                                                     DelayParams::DELAY_MS_MAX);

    return juce::jlimit< float >(DelayParams::DELAY_MS_MIN, DelayParams::DELAY_MS_MAX, parameter_value);
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
XyGraphOverlay::getParameterValueFromYCoordinate(int y_coordinate)
{
    y_coordinate = juce::jlimit< int >(MIN_VALID_COORDINATE, MAX_VALID_COORDINATE, y_coordinate);

    const auto parameter_value = juce::jmap< float >(static_cast< float >(y_coordinate),
                                                     static_cast< float >(MIN_VALID_COORDINATE),
                                                     static_cast< float >(MAX_VALID_COORDINATE),
                                                     DelayParams::FEEDBACK_MAX,
                                                     DelayParams::FEEDBACK_MIN);

    return juce::jlimit< float >(DelayParams::FEEDBACK_MIN, DelayParams::FEEDBACK_MAX, parameter_value);
}

/*---------------------------------------------------------------------------
** End of File
*/
