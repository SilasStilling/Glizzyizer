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
    setColour (juce::Slider::textBoxTextColourId,         onionWhite);
    setColour (juce::Slider::textBoxOutlineColourId,      juce::Colours::transparentBlack);
    setColour (juce::Label::textColourId,                 onionWhite);
    setColour (juce::ToggleButton::textColourId,          onionWhite);
    setColour (juce::ToggleButton::tickColourId,          ketchupRed);
}

void GlizzyLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, float startAngle, float endAngle,
                                          juce::Slider& slider)
{
    const auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (8.0f);
    const auto centre = bounds.getCentre();
    const float fullR = juce::jmin (bounds.getWidth(), bounds.getHeight()) * 0.5f;
    const float angle = startAngle + sliderPos * (endAngle - startAngle);

    // 1) Drop shadow under the knob
    {
        juce::Path shadow;
        shadow.addEllipse (centre.x - fullR, centre.y - fullR + 5.0f, fullR * 2.0f, fullR * 2.0f);
        g.setColour (juce::Colours::black.withAlpha (0.55f));
        g.fillPath (shadow);
    }

    // 2) Outer dark ring (bezel base)
    const float ringR = fullR;
    g.setColour (juce::Colour (0xFF161616));
    g.fillEllipse (centre.x - ringR, centre.y - ringR, ringR * 2.0f, ringR * 2.0f);

    // 3) Bezel ring with vertical light gradient (top-lit cylinder feel)
    const float bezelR = ringR - 4.0f;
    juce::ColourGradient bezel (juce::Colour (0xFF5A5A5A), centre.x, centre.y - bezelR,
                                juce::Colour (0xFF1B1B1B), centre.x, centre.y + bezelR, false);
    g.setGradientFill (bezel);
    g.fillEllipse (centre.x - bezelR, centre.y - bezelR, bezelR * 2.0f, bezelR * 2.0f);

    // 5) Main body — slightly inset, darker, also top-lit
    const float bodyR = bezelR - 4.0f;
    juce::ColourGradient body (juce::Colour (0xFF3C3C3C), centre.x, centre.y - bodyR,
                               juce::Colour (0xFF0C0C0C), centre.x, centre.y + bodyR, false);
    g.setGradientFill (body);
    g.fillEllipse (centre.x - bodyR, centre.y - bodyR, bodyR * 2.0f, bodyR * 2.0f);

    // 5b) Soft top highlight to fake brushed metal sheen
    {
        juce::ColourGradient sheen (juce::Colours::white.withAlpha (0.18f),
                                    centre.x, centre.y - bodyR * 0.95f,
                                    juce::Colours::transparentWhite,
                                    centre.x, centre.y - bodyR * 0.05f, false);
        g.setGradientFill (sheen);
        g.fillEllipse (centre.x - bodyR, centre.y - bodyR, bodyR * 2.0f, bodyR * 2.0f);
    }

    // 6) Inner edge stroke (thin charcoal line for definition)
    g.setColour (juce::Colour (0xFF000000).withAlpha (0.6f));
    g.drawEllipse (centre.x - bodyR, centre.y - bodyR, bodyR * 2.0f, bodyR * 2.0f, 1.0f);

    // 7) Value arc — track + filled portion in mustard
    const float arcR = ringR + 5.0f;
    juce::Path track;
    track.addCentredArc (centre.x, centre.y, arcR, arcR, 0.0f, startAngle, endAngle, true);
    g.setColour (juce::Colours::black.withAlpha (0.55f));
    g.strokePath (track, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    juce::Path val;
    val.addCentredArc (centre.x, centre.y, arcR, arcR, 0.0f, startAngle, angle, true);
    g.setColour (mustardYellow);
    g.strokePath (val, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // 8) Indicator pip — short bright bar near top, rotates with value
    {
        const float pipLen = bodyR * 0.32f;
        const float pipWid = 3.0f;
        juce::Path pip;
        pip.addRoundedRectangle (-pipWid * 0.5f, -bodyR + 5.0f, pipWid, pipLen, 1.5f);
        g.setColour (juce::Colours::white.withAlpha (0.92f));
        g.fillPath (pip, juce::AffineTransform::rotation (angle).translated (centre.x, centre.y));
    }

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
