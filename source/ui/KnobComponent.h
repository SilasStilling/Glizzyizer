#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class KnobComponent : public juce::Component
{
public:
    KnobComponent (juce::AudioProcessorValueTreeState& apvts,
                   const juce::String& parameterId,
                   const juce::String& label,
                   const juce::String& suffix = "");

    void setIcon (juce::Image image);
    void setTooltip (const juce::String& tip);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider slider;
    juce::Label  caption;
    juce::Image  icon;
    juce::Rectangle<int> iconBounds;
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;
};
