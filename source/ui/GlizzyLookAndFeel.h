#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class GlizzyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    GlizzyLookAndFeel();

    void drawRotarySlider (juce::Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider&) override;

    void drawToggleButton (juce::Graphics&, juce::ToggleButton&,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;

    juce::Font getLabelFont (juce::Label&) override;

    static const juce::Colour bunBeige;
    static const juce::Colour mustardYellow;
    static const juce::Colour ketchupRed;
    static const juce::Colour grillCharcoal;
    static const juce::Colour onionWhite;
    static const juce::Colour relishGreen;
};
