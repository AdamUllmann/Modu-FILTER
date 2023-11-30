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
    cutoffKnob.setRange(10.0, 22000.0, 0.01);
    cutoffKnob.setSkewFactorFromMidPoint(1000.0);
    cutoffKnob.setValue(audioProcessor.getCutoffFrequency());
    addAndMakeVisible(&cutoffKnob);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "cutoff", cutoffKnob);

    cutoffKnob.addListener(this);

    resonanceKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    resonanceKnob.setRange(0.01, 32.0, 0.01);
    resonanceKnob.setSkewFactorFromMidPoint(1.0);
    resonanceKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    resonanceKnob.setValue(audioProcessor.getResonance());
    addAndMakeVisible(resonanceKnob);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "resonance", resonanceKnob);
    
    resonanceKnob.addListener(this);

    filterTypeButton.setButtonText("Filter Type: LowPass");
    filterTypeButton.onClick = [this] { filterTypeButtonClicked(); };
    addAndMakeVisible(filterTypeButton);
    filterTypeButton.setClickingTogglesState(true);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameters, "filterType", filterTypeButton);





    //audioProcessor.parameters.addParameterListener("cutoff", this);
    //audioProcessor.parameters.addParameterListener("resonance", this);
    //audioProcessor.parameters.addParameterListener("filterType", this);


}

ModuFilterAudioProcessorEditor::~ModuFilterAudioProcessorEditor()
{
    cutoffKnob.removeListener(this);
    resonanceKnob.removeListener(this);
}

//==============================================================================
void ModuFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(30.0f);

    juce::Font modernFont("Sans-Sarif", 30.0f, juce::Font::bold);
    g.setFont(modernFont);

    juce::Rectangle<int> bounds = getLocalBounds();

    juce::Colour modernColor(0xEE214780);

    g.setColour(modernColor);
    g.fillRect(bounds);

    g.setColour(juce::Colours::white);
    juce::Rectangle<float> roundedRect = bounds.toFloat().reduced(20.0f);
    g.drawRoundedRectangle(roundedRect, 15.0f, 2.0f);

    g.setColour(juce::Colours::white);
    g.drawText("Modu-FILTER", bounds, juce::Justification::centred, true);
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
    filterTypeButton.setBounds(10, 10, 120, 30);
}
