/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ModuFilterAudioProcessorEditor::ModuFilterAudioProcessorEditor (ModuFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);



    cutoffKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    cutoffKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cutoffKnob.setRange(0.01, 22000.0, 0.01);
    cutoffKnob.setSkewFactorFromMidPoint(1000.0);
    cutoffKnob.setValue(audioProcessor.getCutoffFrequency());
    addAndMakeVisible(&cutoffKnob);

    cutoffKnob.addListener(this);

    resonanceKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    resonanceKnob.setRange(0.01, 100.0, 0.01);
    resonanceKnob.setSkewFactorFromMidPoint(1.0);
    resonanceKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    resonanceKnob.setValue(audioProcessor.getResonance());

    addAndMakeVisible(resonanceKnob);
    resonanceKnob.addListener(this);

}

ModuFilterAudioProcessorEditor::~ModuFilterAudioProcessorEditor()
{
    cutoffKnob.removeListener(this);
}

//==============================================================================
void ModuFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient gradient;
    gradient.isRadial = false;
    gradient.point1 = { 0, 0 };
    gradient.point2 = { static_cast<float>(getWidth()), static_cast<float>(getHeight()) };
    gradient.addColour(0.0, juce::Colours::darkgrey);
    gradient.addColour(1.0, juce::Colours::black);

    g.setGradientFill(gradient);
    g.fillRect(getLocalBounds());

    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawFittedText("ModuFilter", getLocalBounds().removeFromTop(30), juce::Justification::centred, 1);
}

void ModuFilterAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    int knobWidth = 100;
    int knobHeight = 100;

    int left = (area.getWidth() - knobWidth) / 2;
    int topCutoff = (area.getHeight() - 2 * knobHeight) / 3;
    int topResonance = topCutoff * 2 + knobHeight;

    cutoffKnob.setBounds(left, topCutoff, knobWidth, knobHeight);
    resonanceKnob.setBounds(left, topResonance, knobWidth, knobHeight);
}
