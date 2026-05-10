#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
    using APVTS = juce::AudioProcessorValueTreeState;

    auto pctRange = juce::NormalisableRange<float> (0.0f, 100.0f, 0.01f);
    auto biRange  = juce::NormalisableRange<float> (-100.0f, 100.0f, 0.01f);
    auto dbRange  = juce::NormalisableRange<float> (-24.0f, 24.0f, 0.01f);
}

GlizzyizerProcessor::GlizzyizerProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMETERS", createLayout())
{
}

APVTS::ParameterLayout GlizzyizerProcessor::createLayout()
{
    using FloatParam = juce::AudioParameterFloat;
    using BoolParam  = juce::AudioParameterBool;

    APVTS::ParameterLayout layout;

    layout.add (std::make_unique<FloatParam> (
        juce::ParameterID { girthId, 1 },   "Girth",   pctRange, 35.0f));

    layout.add (std::make_unique<FloatParam> (
        juce::ParameterID { mustardId, 1 }, "Mustard", biRange,  0.0f));

    layout.add (std::make_unique<BoolParam> (
        juce::ParameterID { onionsId, 1 },  "Onions",  false));

    layout.add (std::make_unique<FloatParam> (
        juce::ParameterID { serveId, 1 },   "Serve",   dbRange,  0.0f));

    return layout;
}

void GlizzyizerProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate       = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels      = static_cast<juce::uint32> (getTotalNumOutputChannels());

    saturator.prepare  (spec);
    tiltEQ.prepare     (spec);
    onionStage.prepare (spec);

    outputGain.prepare (spec);
    outputGain.setRampDurationSeconds (0.02);
}

void GlizzyizerProcessor::releaseResources() {}

bool GlizzyizerProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& mainOut = layouts.getMainOutputChannelSet();
    if (mainOut != juce::AudioChannelSet::mono() && mainOut != juce::AudioChannelSet::stereo())
        return false;

    return mainOut == layouts.getMainInputChannelSet();
}

void GlizzyizerProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto totalNumIn  = getTotalNumInputChannels();
    const auto totalNumOut = getTotalNumOutputChannels();

    for (int ch = totalNumIn; ch < totalNumOut; ++ch)
        buffer.clear (ch, 0, buffer.getNumSamples());

    const float girth01   = apvts.getRawParameterValue (girthId)->load()   * 0.01f;
    const float mustard11 = apvts.getRawParameterValue (mustardId)->load() * 0.01f;
    const bool  onionsOn  = apvts.getRawParameterValue (onionsId)->load()  > 0.5f;
    const float serveDb   = apvts.getRawParameterValue (serveId)->load();

    saturator.setGirth  (girth01);
    tiltEQ.setMustard   (mustard11);
    onionStage.setOnions (onionsOn);
    outputGain.setGainDecibels (serveDb);

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> ctx (block);

    saturator.process  (ctx);
    tiltEQ.process     (ctx);
    onionStage.process (ctx);
    outputGain.process (ctx);
}

juce::AudioProcessorEditor* GlizzyizerProcessor::createEditor()
{
    return new GlizzyizerEditor (*this);
}

void GlizzyizerProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto state = apvts.copyState(); state.isValid())
        if (auto xml = state.createXml())
            copyXmlToBinary (*xml, destData);
}

void GlizzyizerProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GlizzyizerProcessor();
}
