#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class CustomLabel : public juce::Label
{
public:
    explicit CustomLabel(const DelayParams::ParamId& param_id);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLabel)
};
