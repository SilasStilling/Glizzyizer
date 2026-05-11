#include "FlameBoostButton.h"
#include "GlizzyLookAndFeel.h"
#include <BinaryData.h>

FlameBoostButton::FlameBoostButton() : juce::Button ("FLAME BOOST")
{
    setClickingTogglesState (true);
    image = juce::ImageCache::getFromMemory (BinaryData::glizzyizer_flame_png,
                                             BinaryData::glizzyizer_flame_pngSize);
}

void FlameBoostButton::paintButton (juce::Graphics& g, bool isHighlighted, bool isDown)
{
    auto bounds = getLocalBounds().toFloat().reduced (4.0f);
    const bool on = getToggleState();

    const float textH = juce::jmin (34.0f, bounds.getHeight() * 0.22f);
    auto textBox = bounds.removeFromBottom (textH);
    auto iconArea = bounds.withTrimmedTop (16.0f);

    if (image.isValid())
    {
        const float baseAlpha = on ? 1.0f : 0.55f;
        const float boost     = isHighlighted ? 0.10f : 0.0f;
        g.setOpacity (juce::jlimit (0.0f, 1.0f, baseAlpha + boost));

        const float imgRatio = (float) image.getWidth() / (float) image.getHeight();
        const float boxRatio = iconArea.getWidth() / iconArea.getHeight();

        auto target = iconArea;
        if (imgRatio > boxRatio)
            target = target.withSizeKeepingCentre (target.getWidth(), target.getWidth() / imgRatio);
        else
            target = target.withSizeKeepingCentre (target.getHeight() * imgRatio, target.getHeight());

        if (isDown) target = target.reduced (2.0f);

        g.drawImage (image, target, juce::RectanglePlacement::centred);
        g.setOpacity (1.0f);
    }

    const auto titleColour = on ? GlizzyLookAndFeel::onionWhite
                                : GlizzyLookAndFeel::onionWhite.withAlpha (0.85f);
    g.setColour (isHighlighted ? titleColour.brighter (0.15f) : titleColour);

    const float titleSize = juce::jmin (30.0f, textBox.getHeight() * 0.95f);
    g.setFont (juce::Font (juce::FontOptions (titleSize).withStyle ("Bold")));
    g.drawFittedText ("FLAME BOOST", textBox.toNearestInt(),
                      juce::Justification::centred, 1, 0.85f);

    {
        const float ledR = 7.0f;
        auto ledBox = juce::Rectangle<float> (iconArea.getRight() - 100.0f,
                                              iconArea.getCentreY() - 22.0f,
                                              52.0f, 44.0f);
        const auto ledCentre = ledBox.getCentre();
        const auto ledColour = on ? GlizzyLookAndFeel::relishGreen
                                  : GlizzyLookAndFeel::ketchupRed;

        const float glowR = ledR * 2.6f;
        juce::ColourGradient glow (ledColour.withAlpha (on ? 0.6f : 0.35f),
                                   ledCentre.x, ledCentre.y,
                                   ledColour.withAlpha (0.0f),
                                   ledCentre.x + glowR, ledCentre.y, true);
        g.setGradientFill (glow);
        g.fillEllipse (ledCentre.x - glowR, ledCentre.y - glowR, glowR * 2.0f, glowR * 2.0f);

        g.setColour (ledColour);
        g.fillEllipse (ledCentre.x - ledR, ledCentre.y - ledR, ledR * 2.0f, ledR * 2.0f);

        g.setColour (juce::Colours::white.withAlpha (0.55f));
        g.fillEllipse (ledCentre.x - ledR * 0.45f, ledCentre.y - ledR * 0.75f,
                       ledR * 0.7f, ledR * 0.55f);

        g.setColour (GlizzyLookAndFeel::onionWhite.withAlpha (0.85f));
        g.setFont (juce::Font (juce::FontOptions (11.0f).withStyle ("Bold")));
        auto labelBox = juce::Rectangle<float> (ledBox.getX(), ledCentre.y + ledR + 3.0f,
                                                ledBox.getWidth(), 14.0f);
        g.drawText (on ? "ON" : "OFF", labelBox.toNearestInt(),
                    juce::Justification::centred, false);
    }
}
