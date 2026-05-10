#include "OnionsButton.h"
#include "GlizzyLookAndFeel.h"
#include <BinaryData.h>

OnionsButton::OnionsButton() : juce::Button ("ONIONS")
{
    setClickingTogglesState (true);
    image = juce::ImageCache::getFromMemory (BinaryData::glizzyizer_onions_png,
                                             BinaryData::glizzyizer_onions_pngSize);
}

void OnionsButton::paintButton (juce::Graphics& g, bool isHighlighted, bool isDown)
{
    auto bounds = getLocalBounds().toFloat().reduced (3.0f);
    const bool on = getToggleState();

    auto inner = bounds.reduced (10.0f);

    auto headerBox = inner.removeFromTop (24.0f);
    g.setColour (GlizzyLookAndFeel::onionWhite.withAlpha (isHighlighted ? 1.0f : 0.92f));
    g.setFont (juce::Font (juce::FontOptions (20.0f).withStyle ("Bold")));
    g.drawText ("Onions", headerBox.toNearestInt(), juce::Justification::centred, false);

    auto ledBox = inner.removeFromBottom (16.0f);
    {
        const float ledR = 4.5f;
        const auto centre = ledBox.getCentre();
        const auto ledColour = on ? GlizzyLookAndFeel::relishGreen
                                  : GlizzyLookAndFeel::ketchupRed;

        juce::ColourGradient glow (ledColour.withAlpha (on ? 0.7f : 0.55f),
                                   centre.x, centre.y,
                                   ledColour.withAlpha (0.0f),
                                   centre.x + ledR * 3.5f, centre.y, true);
        g.setGradientFill (glow);
        g.fillRect (ledBox.expanded (10.0f, 6.0f));

        g.setColour (ledColour);
        g.fillEllipse (centre.x - ledR, centre.y - ledR, ledR * 2.0f, ledR * 2.0f);

        g.setColour (juce::Colours::white.withAlpha (0.5f));
        g.fillEllipse (centre.x - ledR * 0.45f, centre.y - ledR * 0.75f,
                       ledR * 0.7f, ledR * 0.55f);
    }

    if (image.isValid() && ! inner.isEmpty())
    {
        const float baseAlpha = on ? 1.0f : 0.65f;
        const float boost     = isHighlighted ? 0.10f : 0.0f;
        g.setOpacity (juce::jlimit (0.0f, 1.0f, baseAlpha + boost));

        const float imgRatio = (float) image.getWidth() / (float) image.getHeight();
        const float boxRatio = inner.getWidth() / inner.getHeight();

        auto target = inner;
        if (imgRatio > boxRatio)
            target = target.withSizeKeepingCentre (target.getWidth(), target.getWidth() / imgRatio);
        else
            target = target.withSizeKeepingCentre (target.getHeight() * imgRatio, target.getHeight());

        if (isDown) target = target.reduced (2.0f);

        g.drawImage (image, target, juce::RectanglePlacement::centred);
        g.setOpacity (1.0f);
    }
}
