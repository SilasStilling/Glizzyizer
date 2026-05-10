#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "PluginProcessor.h"
#include "ui/GlizzyLookAndFeel.h"
#include "ui/KnobComponent.h"
#include "ui/OnionsButton.h"

class GlizzyizerEditor : public juce::AudioProcessorEditor
{
public:
    explicit GlizzyizerEditor (GlizzyizerProcessor&);
    ~GlizzyizerEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GlizzyizerProcessor& processor;
    GlizzyLookAndFeel    laf;

    KnobComponent girth;
    KnobComponent mustard;
    KnobComponent serve;

    OnionsButton onionsButton;
    juce::AudioProcessorValueTreeState::ButtonAttachment onionsAttach;

    juce::Image       background;
    juce::Image       logo;
    juce::Image       sausage;
    juce::Rectangle<int> logoBounds;
    juce::Rectangle<int> sausageBounds;
    juce::Rectangle<int> creditBounds;

    juce::TooltipWindow tooltipWindow { this, 600 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlizzyizerEditor)
};
