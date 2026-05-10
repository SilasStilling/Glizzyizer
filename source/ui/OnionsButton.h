#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class OnionsButton : public juce::Button
{
public:
    OnionsButton();

    void paintButton (juce::Graphics&, bool isHighlighted, bool isDown) override;

private:
    juce::Image image;
};
