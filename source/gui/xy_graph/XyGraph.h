#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "XyGraphCanvas.h"
#include "XyGraphOverlay.h"
#include "XyGraphThumb.h"

class XyGraph : public juce::Component
{
public:
    explicit XyGraph(PluginProcessor& processor_ref);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    [[nodiscard]] int getXCoordinateFromParameterValue() const;
    [[nodiscard]] int getYCoordinateFromParameterValue() const;

    PluginProcessor& processor_ref_;

    XyGraphCanvas    canvas_;
    XyGraphThumb     thumb_;
    juce::DropShadow thumb_shadow_;
    XyGraphOverlay   overlay_;

    static constexpr int   THUMB_RADIUS  = Gui::THUMB_DIAMETER / 2;
    static constexpr uint8 SHADOW_RADIUS = Gui::UI_MAGIC_NUMBER;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGraph)
};
