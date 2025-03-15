#pragma once

#include <JuceHeader.h>

#include "RotaryPositionMarker.h"

class RotaryGroup : public juce::Component
{
public:
    RotaryGroup(juce::AudioProcessorValueTreeState& apvts, const Gui::Params::ParamId& param_id);

    void paint(juce::Graphics& g) override;
    void resized() override;

    RotaryPositionMarker& getPositionMarker();

private:
    std::unique_ptr< juce::Drawable > background_image_;
    RotaryPositionMarker              positon_marker_;
    juce::Label                       label_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryGroup)
};
