#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "XyGridCanvas.h"
#include "XyGridOverlay.h"

class XyGrid : public juce::Component
{
public:
    explicit XyGrid(PluginProcessor& processor_ref);

    void resized() override;

private:
    XyGridCanvas  canvas_;
    XyGridOverlay overlay_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XyGrid)
};
