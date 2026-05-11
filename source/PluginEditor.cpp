#include "PluginEditor.h"
#include <BinaryData.h>

GlizzyizerEditor::GlizzyizerEditor (GlizzyizerProcessor& p)
    : juce::AudioProcessorEditor (&p),
      processor (p),
      girth   (p.apvts, GlizzyizerProcessor::girthId,   "GIRTH",   " %"),
      mustard (p.apvts, GlizzyizerProcessor::mustardId, "MUSTARD", " %"),
      serve   (p.apvts, GlizzyizerProcessor::serveId,   "SERVE",   " dB"),
      flameBoostAttach (p.apvts, GlizzyizerProcessor::onionsId, flameBoostButton)
{
    setLookAndFeel (&laf);

    addAndMakeVisible (girth);
    addAndMakeVisible (mustard);
    addAndMakeVisible (serve);
    addAndMakeVisible (flameBoostButton);

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
    flameBoostButton.setTooltip ("Flame Boost — adds a presence lift and high-frequency stereo widener.");

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
    auto area = getLocalBounds().reduced (90, 0).withTrimmedTop (50).withTrimmedBottom (18);
    logoBounds = area.removeFromTop (66);

    auto knobs = area.removeFromTop (176).reduced (20, 0);
    const int knobW = knobs.getWidth() / 3;
    girth  .setBounds (knobs.removeFromLeft (knobW).reduced (10, 2));
    mustard.setBounds (knobs.removeFromLeft (knobW).reduced (10, 2));
    serve  .setBounds (knobs.reduced (10, 2));

    area.removeFromTop (12);
    sausageBounds = area.removeFromTop (40);

    auto bottom = area;
    const int btnH = juce::jmin (170, bottom.getHeight());
    const int btnW = 440;
    flameBoostButton.setBounds (bottom.getCentreX() - btnW / 2,
                                bottom.getBottom() - btnH,
                                btnW, btnH);
}
