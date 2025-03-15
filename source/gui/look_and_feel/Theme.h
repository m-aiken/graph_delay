#pragma once

#include <JuceHeader.h>

class Theme
{
public:
    Theme() = default;

    enum COLOUR {
        EGGSHELL,
        ORANGE,
        DARK_BLUE,
        LIGHT_BLUE,
    };

    static juce::Colour getColour(const COLOUR& colour)
    {
        switch (colour) {
        case EGGSHELL:
            return { 244u, 241u, 222u };

        case ORANGE:
            return { 217u, 85u, 50u };

        case DARK_BLUE:
            return { 3u, 31u, 42u };

        case LIGHT_BLUE:
            return { 58u, 96u, 112u };

        default:
            return { 0, 0, 0 };
        }
    }

    static juce::Font getFont() { return { juce::Font::getDefaultMonospacedFontName(), 14.f, 0 }; }
};
