#include "KnobComponent.h"

KnobComponent::KnobComponent (juce::AudioProcessorValueTreeState& apvts,
                              const juce::String& parameterId,
                              const juce::String& label,
                              const juce::String& suffix)
    : attachment (apvts, parameterId, slider)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 18);
    slider.setTextValueSuffix (suffix);
    addAndMakeVisible (slider);

    caption.setText (label, juce::dontSendNotification);
    caption.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (caption);
}

void KnobComponent::resized()
{
    auto area = getLocalBounds();
    caption.setBounds (area.removeFromTop (22));
    slider.setBounds  (area);
}
