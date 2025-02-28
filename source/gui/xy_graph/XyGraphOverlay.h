#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class XyGraphOverlay : public juce::Component
{
public:
    explicit XyGraphOverlay(PluginProcessor& processor_ref);

    void mouseDrag(const juce::MouseEvent& event) override;

private:
    [[nodiscard]] static float getParameterValueFromXCoordinate(int x_coordinate);
    [[nodiscard]] static float getParameterValueFromYCoordinate(int y_coordinate);

    static constexpr int MIN_VALID_COORDINATE = Gui::THUMB_DIAMETER;
    static constexpr int MAX_VALID_COORDINATE = Gui::GRAPH_DIAMETER - Gui::THUMB_DIAMETER;

    PluginProcessor& processor_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGraphOverlay)
};
