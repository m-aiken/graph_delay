#include "GlobalConstants.h"
#include "XyGraphOverlay.h"

/*---------------------------------------------------------------------------
**
*/
XyGraphOverlay::XyGraphOverlay(PluginProcessor& processor_ref)
{
    x_.referTo(processor_ref.getApvts().getParameterAsValue(Gui::Params::TIME));
    y_.referTo(processor_ref.getApvts().getParameterAsValue(Gui::Params::FEEDBACK));

    setAlwaysOnTop(true);
}

/*---------------------------------------------------------------------------
**
*/
void
XyGraphOverlay::mouseDrag(const juce::MouseEvent& event)
{
    x_ = getParameterValueFromXCoordinate(event.getPosition().getX());
    y_ = getParameterValueFromYCoordinate(event.getPosition().getY());
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
