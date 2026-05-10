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

    setSize (520, 400);
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

    if (logo.isValid() && ! logoBounds.isEmpty())
    {
        const float imgRatio = (float) logo.getWidth() / (float) logo.getHeight();
        const float boxRatio = (float) logoBounds.getWidth() / (float) logoBounds.getHeight();

        auto target = logoBounds.toFloat();
        if (imgRatio > boxRatio)
        {
            const float h = target.getWidth() / imgRatio;
            target = target.withSizeKeepingCentre (target.getWidth(), h);
        }
        else
        {
            const float w = target.getHeight() * imgRatio;
            target = target.withSizeKeepingCentre (w, target.getHeight());
        }

        g.drawImage (logo, target, juce::RectanglePlacement::centred);
    }
}

void GlizzyizerEditor::resized()
{
    auto area = getLocalBounds().reduced (16);
    logoBounds = area.removeFromTop (120);

    auto knobs = area.removeFromTop (200);
    const int knobW = knobs.getWidth() / 3;
    girth  .setBounds (knobs.removeFromLeft (knobW).reduced (8));
    mustard.setBounds (knobs.removeFromLeft (knobW).reduced (8));
    serve  .setBounds (knobs.reduced (8));

    auto bottom = area;
    onionsButton.setBounds (bottom.withSizeKeepingCentre (180, 36));
}
