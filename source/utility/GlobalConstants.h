#pragma once

#include <JuceHeader.h>

namespace Gui
{

static constexpr int WINDOW_WIDTH    = 800;
static constexpr int WINDOW_HEIGHT   = 600;
static constexpr int PADDING         = 20;
static constexpr int GRAPH_DIAMETER  = 320;
static constexpr int ROTARY_DIAMETER = (GRAPH_DIAMETER / 2) - (PADDING * 2);

enum RADIO_GROUP_ID {
    INTERVAL_BUTTONS = 1001,
};

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

namespace IntervalParams
{

enum INTERVAL {
    INTERVAL_1_1,
    INTERVAL_1_2,
    INTERVAL_1_4,
    INTERVAL_1_8,
    INTERVAL_1_16,
    INTERVAL_1_32,
    INTERVAL_1_64,
    NUM_INTERVALS,
};

static constexpr INTERVAL DEFAULT_INTERVAL = INTERVAL_1_4;

static const std::map< INTERVAL, juce::String > INTERVAL_LABEL_MAP = {
    { INTERVAL_1_1, "1/1" },    //
    { INTERVAL_1_2, "1/2" },    //
    { INTERVAL_1_4, "1/4" },    //
    { INTERVAL_1_8, "1/8" },    //
    { INTERVAL_1_16, "1/16" },  //
    { INTERVAL_1_32, "1/32" },  //
    { INTERVAL_1_64, "1/64" },  //
};

static juce::String
getIntervalLabel(const INTERVAL& interval)
{
    return INTERVAL_LABEL_MAP.at(interval);
}

}  // namespace IntervalParams