#include "OnionStage.h"

void OnionStage::prepare (const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;

    presence.prepare (spec);
    *presence.state = *Coeffs::makePeakFilter (sampleRate, 4500.0f, 0.7f,
                                               juce::Decibels::decibelsToGain (3.0f));

    juce::dsp::ProcessSpec monoSpec { spec.sampleRate, spec.maximumBlockSize, 1 };
    sideShelf.prepare (monoSpec);
    sideShelf.coefficients = Coeffs::makeHighShelf (sampleRate, 2000.0f, 0.707f,
                                                    juce::Decibels::decibelsToGain (3.0f));
}

void OnionStage::reset()
{
    presence.reset();
    sideShelf.reset();
}

void OnionStage::setOnions (bool e)
{
    if (e == enabled) return;
    enabled = e;
    if (! enabled)
    {
        presence.reset();
        sideShelf.reset();
    }
}

void OnionStage::process (const juce::dsp::ProcessContextReplacing<float>& context)
{
    if (! enabled)
        return;

    auto& block = context.getOutputBlock();

    presence.process (context);

    if (block.getNumChannels() >= 2)
    {
        const auto numSamples = block.getNumSamples();
        auto* left  = block.getChannelPointer (0);
        auto* right = block.getChannelPointer (1);

        for (size_t i = 0; i < numSamples; ++i)
        {
            const float L = left[i];
            const float R = right[i];
            const float mid  = 0.5f * (L + R);
            float side       = 0.5f * (L - R);

            side = sideShelf.processSample (side);

            left[i]  = mid + side;
            right[i] = mid - side;
        }
    }
}
