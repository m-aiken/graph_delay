#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class IntervalAnnotations : public juce::Component
{
public:
    IntervalAnnotations();

    void resized() override;

private:
    std::array< std::unique_ptr< juce::Label >, Gui::Params::NUM_INTERVALS > labels_;

    static constexpr float START_ANGLE = juce::degreesToRadians(180.f + 45.f);
    static constexpr float END_ANGLE   = juce::degreesToRadians(180.f - 45.f) + juce::MathConstants< float >::twoPi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IntervalAnnotations)
};
