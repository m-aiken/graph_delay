#pragma once

#include <JuceHeader.h>

#include "IntervalAnnotations.h"
#include "IntervalControl.h"

class AnnotatedIntervalControl : public juce::Component
{
public:
    explicit AnnotatedIntervalControl(juce::AudioProcessorValueTreeState& apvts);

    void resized() override;

private:
    IntervalControl     rotary_;
    IntervalAnnotations interval_annotations_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnnotatedIntervalControl)
};
