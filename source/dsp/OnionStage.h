#pragma once

#include <juce_dsp/juce_dsp.h>

class OnionStage
{
public:
    void prepare (const juce::dsp::ProcessSpec& spec);
    void reset();

    void setOnions (bool enabled);

    void process (const juce::dsp::ProcessContextReplacing<float>& context);

private:
    using Filter     = juce::dsp::IIR::Filter<float>;
    using Coeffs     = juce::dsp::IIR::Coefficients<float>;
    using Duplicator = juce::dsp::ProcessorDuplicator<Filter, Coeffs>;

    Duplicator presence;
    Filter     sideShelf;

    double sampleRate { 44100.0 };
    bool   enabled    { false };
};
