#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "XyGraphCanvas.h"
#include "XyGraphOverlay.h"

class XyGraph : public juce::Component
{
public:
    explicit XyGraph(PluginProcessor& processor_ref);

    void resized() override;

private:
    XyGraphCanvas  canvas_;
    XyGraphOverlay overlay_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGraph)
};
