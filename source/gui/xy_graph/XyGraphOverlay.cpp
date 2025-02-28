#include "GlobalConstants.h"
#include "XyGraphOverlay.h"

/*---------------------------------------------------------------------------
**
*/
XyGraphOverlay::XyGraphOverlay(PluginProcessor& processor_ref)
    : processor_ref_(processor_ref)
{
    setAlwaysOnTop(true);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraphOverlay::mouseDrag(const juce::MouseEvent& event)
{
    juce::RangedAudioParameter* time_param     = processor_ref_.getApvts().getParameter(Gui::Params::TIME);
    juce::RangedAudioParameter* feedback_param = processor_ref_.getApvts().getParameter(Gui::Params::FEEDBACK);

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
                                                     Gui::Params::DELAY_MS_MIN,
                                                     Gui::Params::DELAY_MS_MAX);

    return juce::jlimit< float >(Gui::Params::DELAY_MS_MIN, Gui::Params::DELAY_MS_MAX, parameter_value);
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
                                                     Gui::Params::FEEDBACK_MAX,
                                                     Gui::Params::FEEDBACK_MIN);

    return juce::jlimit< float >(Gui::Params::FEEDBACK_MIN, Gui::Params::FEEDBACK_MAX, parameter_value);
}

/*---------------------------------------------------------------------------
** End of File
*/
