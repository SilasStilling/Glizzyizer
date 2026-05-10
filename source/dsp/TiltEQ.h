#pragma once

#include <juce_dsp/juce_dsp.h>

class TiltEQ
{
public:
    void prepare (const juce::dsp::ProcessSpec& spec);
    void reset();

    void setMustard (float mustard11);

    void process (const juce::dsp::ProcessContextReplacing<float>& context);

private:
    using Filter     = juce::dsp::IIR::Filter<float>;
    using Coeffs     = juce::dsp::IIR::Coefficients<float>;
    using Duplicator = juce::dsp::ProcessorDuplicator<Filter, Coeffs>;

    Duplicator lowShelf;
    Duplicator highShelf;

    double sampleRate { 44100.0 };

    static constexpr float lowFreq  = 250.0f;
    static constexpr float highFreq = 4000.0f;
    static constexpr float maxDb    = 6.0f;

    void updateCoefficients (float gainDb);
};
