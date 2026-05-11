#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class FlameBoostButton : public juce::Button
{
public:
    FlameBoostButton();

    void paintButton (juce::Graphics&, bool isHighlighted, bool isDown) override;

private:
    juce::Image image;
};
