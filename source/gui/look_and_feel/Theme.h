#pragma once

#include <JuceHeader.h>

class Theme
{
public:
    Theme() = default;

    enum COLOUR {
        EGGSHELL,
        SALMON,
        BLUE,
        GREEN,
        YELLOW,
    };

    static juce::Colour getColour(const COLOUR& colour)
    {
        switch (colour) {
        case EGGSHELL:
            return { 244u, 241u, 222u };

        case SALMON:
            return { 224u, 122u, 95u };

        case BLUE:
            return { 61u, 64u, 91u };

        case GREEN:
            return { 129u, 178u, 154u };

        case YELLOW:
            return { 242u, 204u, 143u };

        default:
            return { 0, 0, 0 };
        }
    }

    static juce::Font getFont() { return { juce::Font::getDefaultMonospacedFontName(), 14.f, 0 }; }
};
