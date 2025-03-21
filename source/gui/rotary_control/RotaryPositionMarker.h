#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class RotaryPositionMarker
    : public juce::Slider
    , public juce::AudioProcessorParameter::Listener
{
public:
    RotaryPositionMarker(juce::AudioProcessorValueTreeState& apvts, const GraphDelay::ParamId& param_id);
    ~RotaryPositionMarker() override;

    void paint(juce::Graphics& g) override;
    void mouseEnter(const juce::MouseEvent& event) override;

    void parameterValueChanged(int parameter_index, float new_value) override;
    void parameterGestureChanged(int parameter_index, bool gesture_is_starting) override;

private:
    [[nodiscard]] float getValueToDraw() const;

    static constexpr float START_ANGLE = juce::degreesToRadians(180.f + 45.f);
    static constexpr float END_ANGLE   = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants< float >::twoPi;

    juce::RangedAudioParameter* param_;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment ApvtsAttachment;
    std::unique_ptr< ApvtsAttachment >                           slider_attachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryPositionMarker)
};
