#include "PluginEditor.h"
#include <BinaryData.h>

GlizzyizerEditor::GlizzyizerEditor (GlizzyizerProcessor& p)
    : juce::AudioProcessorEditor (&p),
      processor (p),
      girth   (p.apvts, GlizzyizerProcessor::girthId,   "GIRTH",   " %"),
      mustard (p.apvts, GlizzyizerProcessor::mustardId, "MUSTARD", " %"),
      serve   (p.apvts, GlizzyizerProcessor::serveId,   "SERVE",   " dB"),
      onionsAttach (p.apvts, GlizzyizerProcessor::onionsId, onionsButton)
{
    setLookAndFeel (&laf);

    addAndMakeVisible (girth);
    addAndMakeVisible (mustard);
    addAndMakeVisible (serve);
    addAndMakeVisible (onionsButton);

    background = juce::ImageCache::getFromMemory (BinaryData::glizzyizer_background_png,
                                                   BinaryData::glizzyizer_background_pngSize);

    logo = juce::ImageCache::getFromMemory (BinaryData::glizzyizer_logo_png,
                                            BinaryData::glizzyizer_logo_pngSize);

    sausage = juce::ImageCache::getFromMemory (BinaryData::glizzyizer_sausage_png,
                                               BinaryData::glizzyizer_sausage_pngSize);

    girth.setIcon (juce::ImageCache::getFromMemory (BinaryData::glizzyizer_girth_png,
                                                    BinaryData::glizzyizer_girth_pngSize));
    mustard.setIcon (juce::ImageCache::getFromMemory (BinaryData::glizzyizer_mustard_png,
                                                      BinaryData::glizzyizer_mustard_pngSize));
    serve.setIcon (juce::ImageCache::getFromMemory (BinaryData::glizzyizer_serve_png,
                                                    BinaryData::glizzyizer_serve_pngSize));

    girth.setTooltip   ("Drives the signal into a tanh saturator. Higher = thicker, dirtier saturation.");
    mustard.setTooltip ("Tilt EQ. Left = darker / heavier lows. Right = brighter / fizzier highs.");
    serve.setTooltip   ("Output gain in dB. Final volume after the saturation chain.");
    onionsButton.setTooltip ("Toggles a presence boost plus high-frequency stereo widener.");

    setSize (960, 540);
}

GlizzyizerEditor::~GlizzyizerEditor()
{
    setLookAndFeel (nullptr);
}

void GlizzyizerEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    if (background.isValid())
    {
        g.drawImage (background, bounds, juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        juce::ColourGradient bg (GlizzyLookAndFeel::bunBeige.brighter (0.10f), 0.0f, 0.0f,
                                 GlizzyLookAndFeel::bunBeige.darker   (0.20f), 0.0f, bounds.getHeight(),
                                 false);
        g.setGradientFill (bg);
        g.fillAll();
    }

    auto drawAspectFit = [&] (const juce::Image& img, juce::Rectangle<int> box)
    {
        if (! img.isValid() || box.isEmpty()) return;
        const float imgRatio = (float) img.getWidth() / (float) img.getHeight();
        const float boxRatio = (float) box.getWidth()  / (float) box.getHeight();

        auto target = box.toFloat();
        if (imgRatio > boxRatio)
            target = target.withSizeKeepingCentre (target.getWidth(), target.getWidth() / imgRatio);
        else
            target = target.withSizeKeepingCentre (target.getHeight() * imgRatio, target.getHeight());

        g.drawImage (img, target, juce::RectanglePlacement::centred);
    };

    drawAspectFit (logo,    logoBounds);
    drawAspectFit (sausage, sausageBounds);
}

void GlizzyizerEditor::resized()
{
    auto area = getLocalBounds().reduced (24);
    logoBounds = area.removeFromTop (90);

    auto knobs = area.removeFromTop (200).reduced (60, 0);
    const int knobW = knobs.getWidth() / 3;
    girth  .setBounds (knobs.removeFromLeft (knobW).reduced (20, 4));
    mustard.setBounds (knobs.removeFromLeft (knobW).reduced (20, 4));
    serve  .setBounds (knobs.reduced (20, 4));

    sausageBounds = area.removeFromTop (50);

    auto bottom = area;
    onionsButton.setBounds (bottom.withSizeKeepingCentre (240, 140));
}
