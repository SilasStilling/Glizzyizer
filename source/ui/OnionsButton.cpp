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
    auto bounds = getLocalBounds().toFloat().reduced (2.0f);
    const bool on = getToggleState();

    auto imgBox = bounds.removeFromTop (bounds.getHeight() - 22.0f);
    auto txtBox = bounds;

    if (on)
    {
        const auto centre = imgBox.getCentre();
        const float radius = juce::jmax (imgBox.getWidth(), imgBox.getHeight()) * 0.55f;
        juce::ColourGradient glow (GlizzyLookAndFeel::relishGreen.withAlpha (0.55f),
                                   centre.x, centre.y,
                                   GlizzyLookAndFeel::relishGreen.withAlpha (0.0f),
                                   centre.x + radius, centre.y, true);
        g.setGradientFill (glow);
        g.fillRect (imgBox.expanded (10.0f));
    }

    if (image.isValid())
    {
        const float baseAlpha = on ? 1.0f : 0.40f;
        const float boost     = isHighlighted ? 0.10f : 0.0f;
        g.setOpacity (juce::jlimit (0.0f, 1.0f, baseAlpha + boost));

        const float imgRatio = (float) image.getWidth() / (float) image.getHeight();
        const float boxRatio = imgBox.getWidth() / imgBox.getHeight();

        auto target = imgBox;
        if (imgRatio > boxRatio)
            target = target.withSizeKeepingCentre (target.getWidth(), target.getWidth() / imgRatio);
        else
            target = target.withSizeKeepingCentre (target.getHeight() * imgRatio, target.getHeight());

        if (isDown) target = target.reduced (2.0f);

        g.drawImage (image, target, juce::RectanglePlacement::centred);
        g.setOpacity (1.0f);
    }

    g.setColour (on ? GlizzyLookAndFeel::relishGreen.brighter (0.2f) : GlizzyLookAndFeel::onionWhite);
    g.setFont (juce::Font (juce::FontOptions (14.0f).withStyle ("Bold")));
    g.drawFittedText ("ONIONS", txtBox.toNearestInt(), juce::Justification::centred, 1);
}
