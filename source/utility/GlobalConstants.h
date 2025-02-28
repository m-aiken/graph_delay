#pragma once

#include <JuceHeader.h>

namespace Gui
{

static constexpr int UI_MULTIPLE     = 16;
static constexpr int WINDOW_WIDTH    = (UI_MULTIPLE * 50);
static constexpr int WINDOW_HEIGHT   = (UI_MULTIPLE * 40);
static constexpr int GRAPH_DIAMETER  = (UI_MULTIPLE * 20);
static constexpr int THUMB_DIAMETER  = (UI_MULTIPLE * 1);
static constexpr int ROTARY_DIAMETER = (UI_MULTIPLE * 6);
static constexpr int LABEL_HEIGHT    = (UI_MULTIPLE * 2);

enum RADIO_GROUP_ID {
    INTERVAL_BUTTONS = 1001,
};

namespace Params
{
    typedef juce::String ParamId;

    static const ParamId TIME                 = "Time";
    static const ParamId DISCRETE_TIME        = "Discrete Time";
    static const ParamId FEEDBACK             = "Feedback";
    static const ParamId WET_LEVEL            = "Wet";
    static const ParamId DRY_LEVEL            = "Dry";
    static const ParamId TIME_MODE            = "Time Mode";
    static const ParamId TEMPO                = "Tempo";
    static const ParamId TIME_SIG_NUMERATOR   = "Time Sig Numerator";
    static const ParamId TIME_SIG_DENOMINATOR = "Time Sig Denominator";
    static const ParamId RHYTHMIC_INTERVAL    = "Rhythmic Interval";

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

    static constexpr int TEMPO_MIN     = 1;
    static constexpr int TEMPO_MAX     = 240;
    static constexpr int TEMPO_DEFAULT = 120;

    // Currently hardcoding the time signature to 4/4.
    // The user/host will ultimately be able to change it though (just not yet...).
    static constexpr int TIME_SIG_NTOR_MIN     = 3;
    static constexpr int TIME_SIG_NTOR_MAX     = 6;
    static constexpr int TIME_SIG_NTOR_DEFAULT = 4;

    static constexpr int TIME_SIG_DTOR_MIN     = 4;
    static constexpr int TIME_SIG_DTOR_MAX     = 8;
    static constexpr int TIME_SIG_DTOR_DEFAULT = 4;

    enum TIME_MODE_OPTION {
        TIME_MODE_FREE,
        TIME_MODE_QUANTISED,
        NUM_TIME_MODE_OPTIONS,
    };

    static constexpr TIME_MODE_OPTION DEFAULT_TIME_MODE = TIME_MODE_FREE;

    static const std::map< TIME_MODE_OPTION, juce::String > TIME_MODE_OPTION_MAP = {
        { TIME_MODE_FREE, "Free" },
        { TIME_MODE_QUANTISED, "Quantised" },
    };

    static juce::String getTimeModeLabel(const TIME_MODE_OPTION& mode) { return TIME_MODE_OPTION_MAP.at(mode); }

    enum INTERVAL {
        INTERVAL_1_1,
        INTERVAL_1_2,
        INTERVAL_1_4,
        INTERVAL_1_8,
        INTERVAL_1_16,
        INTERVAL_1_32,
        INTERVAL_1_64,
        NUM_INTERVALS,
        FIRST_INTERVAL = INTERVAL_1_1,
        LAST_INTERVAL  = INTERVAL_1_64,
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

    static juce::String getIntervalLabel(const INTERVAL& interval) { return INTERVAL_LABEL_MAP.at(interval); }

}  // namespace Params

}  // namespace Gui
