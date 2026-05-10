#include "GlizzyLookAndFeel.h"

const juce::Colour GlizzyLookAndFeel::bunBeige      { 0xFFE8C77A };
const juce::Colour GlizzyLookAndFeel::mustardYellow { 0xFFFFC72C };
const juce::Colour GlizzyLookAndFeel::ketchupRed    { 0xFFC8242A };
const juce::Colour GlizzyLookAndFeel::grillCharcoal { 0xFF2A1E18 };
const juce::Colour GlizzyLookAndFeel::onionWhite    { 0xFFF6EEDC };
const juce::Colour GlizzyLookAndFeel::relishGreen   { 0xFF7DB249 };

GlizzyLookAndFeel::GlizzyLookAndFeel()
{
    setColour (juce::Slider::rotarySliderFillColourId,    mustardYellow);
    setColour (juce::Slider::rotarySliderOutlineColourId, grillCharcoal);
    setColour (juce::Slider::thumbColourId,               ketchupRed);
    setColour (juce::Label::textColourId,                 grillCharcoal);
    setColour (juce::ToggleButton::textColourId,          grillCharcoal);
    setColour (juce::ToggleButton::tickColourId,          ketchupRed);
}

void GlizzyLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, float startAngle, float endAngle,
                                          juce::Slider& slider)
{
    const auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (6.0f);
    const auto centre = bounds.getCentre();
    const auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) * 0.5f;
    const float angle = startAngle + sliderPos * (endAngle - startAngle);

    juce::Path body;
    body.addEllipse (centre.x - radius, centre.y - radius, radius * 2.0f, radius * 2.0f);

    juce::ColourGradient grad (bunBeige.brighter (0.2f),  centre.x, centre.y - radius,
                               bunBeige.darker   (0.35f), centre.x, centre.y + radius, false);
    g.setGradientFill (grad);
    g.fillPath (body);

    g.setColour (grillCharcoal);
    g.strokePath (body, juce::PathStrokeType (2.0f));

    juce::Path arc;
    arc.addCentredArc (centre.x, centre.y, radius - 8.0f, radius - 8.0f,
                       0.0f, startAngle, endAngle, true);
    g.setColour (grillCharcoal.withAlpha (0.25f));
    g.strokePath (arc, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                              juce::PathStrokeType::rounded));

    juce::Path fill;
    fill.addCentredArc (centre.x, centre.y, radius - 8.0f, radius - 8.0f,
                        0.0f, startAngle, angle, true);
    g.setColour (mustardYellow);
    g.strokePath (fill, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                               juce::PathStrokeType::rounded));

    juce::Path indicator;
    const float pointerLen = radius - 14.0f;
    const float pointerWid = 3.0f;
    indicator.addRoundedRectangle (-pointerWid * 0.5f, -radius + 6.0f,
                                   pointerWid, pointerLen, 1.5f);
    g.setColour (ketchupRed);
    g.fillPath (indicator, juce::AffineTransform::rotation (angle).translated (centre.x, centre.y));

    juce::ignoreUnused (slider);
}

void GlizzyLookAndFeel::drawToggleButton (juce::Graphics& g, juce::ToggleButton& button,
                                          bool isHighlighted, bool isDown)
{
    const auto bounds = button.getLocalBounds().toFloat().reduced (3.0f);
    const float radius = 10.0f;

    auto fill = button.getToggleState() ? relishGreen : onionWhite.darker (0.05f);
    if (isHighlighted) fill = fill.brighter (0.05f);
    if (isDown)        fill = fill.darker   (0.10f);

    g.setColour (fill);
    g.fillRoundedRectangle (bounds, radius);

    g.setColour (grillCharcoal);
    g.drawRoundedRectangle (bounds, radius, 2.0f);

    g.setColour (button.getToggleState() ? onionWhite : grillCharcoal);
    g.setFont (juce::Font (juce::FontOptions (15.0f).withStyle ("Bold")));
    g.drawFittedText (button.getButtonText(), bounds.toNearestInt(),
                      juce::Justification::centred, 1);
}

juce::Font GlizzyLookAndFeel::getLabelFont (juce::Label&)
{
    return juce::Font (juce::FontOptions (14.0f).withStyle ("Bold"));
}
