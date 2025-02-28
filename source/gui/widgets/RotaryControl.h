#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class RotaryControl
    : public juce::Slider
    , public juce::AudioProcessorParameter::Listener
{
public:
    RotaryControl(juce::AudioProcessorValueTreeState& apvts, const Gui::Params::ParamId& param_id);
    ~RotaryControl() override;

    void paint(juce::Graphics& g) override;
    void mouseEnter(const juce::MouseEvent& event) override;

    void parameterValueChanged(int parameter_index, float new_value) override;
    void parameterGestureChanged(int parameter_index, bool gesture_is_starting) override;

protected:
    [[nodiscard]] virtual float getValueToDraw() const;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment ApvtsAttachment;

    juce::RangedAudioParameter*        param_;
    std::unique_ptr< ApvtsAttachment > slider_attachment_;

    static constexpr float START_ANGLE = juce::degreesToRadians(180.f + 45.f);
    static constexpr float END_ANGLE   = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants< float >::twoPi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryControl)
};
