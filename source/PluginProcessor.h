#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

#include "dsp/Saturator.h"
#include "dsp/TiltEQ.h"
#include "dsp/OnionStage.h"

class GlizzyizerProcessor : public juce::AudioProcessor
{
public:
    GlizzyizerProcessor();
    ~GlizzyizerProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Glizzyizer"; }
    bool acceptsMidi() const override  { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override               { return 1; }
    int getCurrentProgram() override            { return 0; }
    void setCurrentProgram (int) override       {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

    static constexpr auto girthId   = "girth";
    static constexpr auto mustardId = "mustard";
    static constexpr auto onionsId  = "onions";
    static constexpr auto serveId   = "serve";

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();

    Saturator   saturator;
    TiltEQ      tiltEQ;
    OnionStage  onionStage;

    juce::dsp::Gain<float> outputGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlizzyizerProcessor)
};
