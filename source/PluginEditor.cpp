#include "PluginEditor.h"

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

    title.setText ("GLIZZYIZER", juce::dontSendNotification);
    title.setJustificationType (juce::Justification::centred);
    title.setFont (juce::Font (juce::FontOptions (28.0f).withStyle ("Bold")));
    title.setColour (juce::Label::textColourId, GlizzyLookAndFeel::ketchupRed);
    addAndMakeVisible (title);

    setSize (520, 320);
}

GlizzyizerEditor::~GlizzyizerEditor()
{
    setLookAndFeel (nullptr);
}

void GlizzyizerEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    juce::ColourGradient bg (GlizzyLookAndFeel::bunBeige.brighter (0.10f), 0.0f, 0.0f,
                             GlizzyLookAndFeel::bunBeige.darker   (0.20f), 0.0f, bounds.getHeight(),
                             false);
    g.setGradientFill (bg);
    g.fillAll();

    g.setColour (GlizzyLookAndFeel::grillCharcoal.withAlpha (0.15f));
    for (float y = 0.0f; y < bounds.getHeight(); y += 14.0f)
        g.drawHorizontalLine ((int) y, 0.0f, bounds.getWidth());

    g.setColour (GlizzyLookAndFeel::grillCharcoal);
    g.drawRoundedRectangle (bounds.reduced (4.0f), 12.0f, 2.5f);
}

void GlizzyizerEditor::resized()
{
    auto area = getLocalBounds().reduced (16);
    title.setBounds (area.removeFromTop (44));

    auto knobs = area.removeFromTop (200);
    const int knobW = knobs.getWidth() / 3;
    girth  .setBounds (knobs.removeFromLeft (knobW).reduced (8));
    mustard.setBounds (knobs.removeFromLeft (knobW).reduced (8));
    serve  .setBounds (knobs.reduced (8));

    auto bottom = area;
    onionsButton.setBounds (bottom.withSizeKeepingCentre (180, 36));
}
