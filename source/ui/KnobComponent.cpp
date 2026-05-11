#include "KnobComponent.h"

KnobComponent::KnobComponent (juce::AudioProcessorValueTreeState& apvts,
                              const juce::String& parameterId,
                              const juce::String& label,
                              const juce::String& suffix)
    : attachment (apvts, parameterId, slider)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 96, 22);
    slider.setTextValueSuffix (suffix);
    addAndMakeVisible (slider);

    caption.setText (label, juce::dontSendNotification);
    caption.setJustificationType (juce::Justification::centred);
    caption.setFont (juce::Font (juce::FontOptions (17.0f).withStyle ("Bold")));
    addAndMakeVisible (caption);
}

void KnobComponent::setIcon (juce::Image image)
{
    icon = std::move (image);
    repaint();
}

void KnobComponent::setTooltip (const juce::String& tip)
{
    slider.setTooltip (tip);
    caption.setTooltip (tip);
}

void KnobComponent::paint (juce::Graphics& g)
{
    if (! icon.isValid() || iconBounds.isEmpty())
        return;

    const float imgRatio = (float) icon.getWidth() / (float) icon.getHeight();
    const float boxRatio = (float) iconBounds.getWidth() / (float) iconBounds.getHeight();

    auto target = iconBounds.toFloat();
    if (imgRatio > boxRatio)
        target = target.withSizeKeepingCentre (target.getWidth(), target.getWidth() / imgRatio);
    else
        target = target.withSizeKeepingCentre (target.getHeight() * imgRatio, target.getHeight());

    g.drawImage (icon, target, juce::RectanglePlacement::centred);
}

void KnobComponent::resized()
{
    auto area = getLocalBounds();
    iconBounds = area.removeFromTop (78);
    caption.setBounds (area.removeFromTop (24));
    slider.setBounds  (area);
}
