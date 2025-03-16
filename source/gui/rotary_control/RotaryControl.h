#pragma once

#include <JuceHeader.h>

#include "RotaryPositionMarker.h"

class RotaryControl : public juce::Component
{
public:
    RotaryControl(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    std::unique_ptr< juce::Drawable > background_image_;
    RotaryPositionMarker              positon_marker_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryControl)
};
