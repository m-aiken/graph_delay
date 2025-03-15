#pragma once

#include <JuceHeader.h>

namespace GraphDelay
{

static constexpr int UI_MAGIC_NUMBER = 16;
static constexpr int WINDOW_WIDTH    = (UI_MAGIC_NUMBER * 42);
static constexpr int WINDOW_HEIGHT   = (UI_MAGIC_NUMBER * 28);
static constexpr int GRAPH_DIAMETER  = (UI_MAGIC_NUMBER * 20);
static constexpr int THUMB_DIAMETER  = (UI_MAGIC_NUMBER * 1);
static constexpr int ROTARY_DIAMETER = (UI_MAGIC_NUMBER * 6);
static constexpr int LABEL_HEIGHT    = (UI_MAGIC_NUMBER * 2);

typedef juce::String ParamId;

static const ParamId TIME      = "Time";
static const ParamId FEEDBACK  = "Feedback";
static const ParamId WET_LEVEL = "Wet";
static const ParamId DRY_LEVEL = "Dry";

static constexpr float DELAY_MS_MIN     = 1.f;
static constexpr float DELAY_MS_MAX     = 999.f;
static constexpr float DELAY_MS_DEFAULT = 400.f;
static constexpr float DELAY_INTERVAL   = 1.f;

static constexpr float FEEDBACK_MIN      = 0.00f;
static constexpr float FEEDBACK_MAX      = 1.00f;
static constexpr float FEEDBACK_DEFAULT  = 0.50f;
static constexpr float FEEDBACK_INTERVAL = 0.01f;

static constexpr float DB_MIN               = -60.f;
static constexpr float DB_MAX               = 0.f;
static constexpr float DB_DEFAULT_DRY_LEVEL = 0.f;
static constexpr float DB_DEFAULT_WET_LEVEL = -6.f;
static constexpr float DB_INTERVAL          = 1.f;

}  // namespace GraphDelay
