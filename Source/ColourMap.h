/*
  ==============================================================================

    ColourMap.h
    Created: 8 Apr 2022 12:05:16am
    Author:  Matt Aiken

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
namespace ColourMap
{

enum Palette
{
    Eggshell,
    Salmon,
    Blue,
    Green,
    Yellow
};

inline std::map<Palette, juce::Colour> colourMap =
{
    { Eggshell, juce::Colour(244u, 241u, 222u) },
    { Salmon,   juce::Colour(224u, 122u, 95u)  },
    { Blue,     juce::Colour(61u, 64u, 91u)    },
    { Green,    juce::Colour(129u, 178u, 154u) },
    { Yellow,   juce::Colour(242u, 204u, 143u) }
};

inline juce::Colour getColour(Palette c) { return colourMap[c]; }

}
