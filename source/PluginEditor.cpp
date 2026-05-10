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
    auto area = getLocalBounds().reduced (16);
    logoBounds = area.removeFromTop (120);

    auto knobs = area.removeFromTop (140).reduced (40, 0);
    const int knobW = knobs.getWidth() / 3;
    girth  .setBounds (knobs.removeFromLeft (knobW).reduced (18, 8));
    mustard.setBounds (knobs.removeFromLeft (knobW).reduced (18, 8));
    serve  .setBounds (knobs.reduced (18, 8));

    sausageBounds = area.removeFromTop (60);

    auto bottom = area;
    onionsButton.setBounds (bottom.withSizeKeepingCentre (180, 36));
}
