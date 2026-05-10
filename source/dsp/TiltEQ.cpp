#include "TiltEQ.h"

void TiltEQ::prepare (const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    lowShelf.prepare (spec);
    highShelf.prepare (spec);
    updateCoefficients (0.0f);
}

void TiltEQ::reset()
{
    lowShelf.reset();
    highShelf.reset();
}

void TiltEQ::setMustard (float mustard11)
{
    mustard11 = juce::jlimit (-1.0f, 1.0f, mustard11);
    updateCoefficients (mustard11 * maxDb);
}

void TiltEQ::updateCoefficients (float gainDb)
{
    const float lowGain  = juce::Decibels::decibelsToGain (-gainDb);
    const float highGain = juce::Decibels::decibelsToGain ( gainDb);

    *lowShelf.state  = *Coeffs::makeLowShelf  (sampleRate, lowFreq,  0.707f, lowGain);
    *highShelf.state = *Coeffs::makeHighShelf (sampleRate, highFreq, 0.707f, highGain);
}

void TiltEQ::process (const juce::dsp::ProcessContextReplacing<float>& context)
{
    lowShelf.process (context);
    highShelf.process (context);
}
