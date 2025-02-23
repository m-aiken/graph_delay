#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "XyGraphThumb.h"

class XyGraphOverlay : public juce::Component
{
public:
    explicit XyGraphOverlay(PluginProcessor& processor_ref);

    void paint(juce::Graphics& g) override;
    void mouseDrag(const juce::MouseEvent& event) override;

private:
    [[nodiscard]] int          getXCoordinateFromParameterValue() const;
    [[nodiscard]] int          getYCoordinateFromParameterValue() const;
    [[nodiscard]] static float getParameterValueFromXCoordinate(int x_coordinate);
    [[nodiscard]] static float getParameterValueFromYCoordinate(int y_coordinate);

    static constexpr int   THUMB_DIAMETER       = 20;
    static constexpr int   THUMB_RADIUS         = THUMB_DIAMETER / 2;
    static constexpr int   MIN_VALID_COORDINATE = THUMB_DIAMETER;
    static constexpr int   MAX_VALID_COORDINATE = Gui::GRAPH_DIAMETER - THUMB_DIAMETER;
    static constexpr uint8 SHADOW_RADIUS        = 15;

    PluginProcessor& processor_ref_;

    XyGraphThumb     thumb_;
    juce::DropShadow thumb_shadow_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGraphOverlay)
};
