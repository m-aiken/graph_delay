#pragma once

#include <JuceHeader.h>

namespace Gui
{

static constexpr int WINDOW_WIDTH    = 600;
static constexpr int WINDOW_HEIGHT   = 400;
static constexpr int ROTARY_DIAMETER = 100;
static constexpr int GRAPH_DIAMETER  = 320;

}  // namespace Gui

namespace DelayParams
{

static constexpr float DELAY_MS_MIN     = 0.f;
static constexpr float DELAY_MS_MAX     = 1000.f;
static constexpr float DELAY_MS_DEFAULT = 400.f;

static constexpr float FEEDBACK_MIN     = 0.f;
static constexpr float FEEDBACK_MAX     = 1.f;
static constexpr float FEEDBACK_DEFAULT = 0.5f;

static constexpr float DB_MIN               = -60.f;
static constexpr float DB_MAX               = 0.f;
static constexpr float DB_DEFAULT_WET_LEVEL = -6.f;

typedef juce::String ParamId;

static const ParamId TIME      = "Time";
static const ParamId FEEDBACK  = "Feedback";
static const ParamId WET_LEVEL = "Wet";
static const ParamId DRY_LEVEL = "Dry";

}  // namespace DelayParams
