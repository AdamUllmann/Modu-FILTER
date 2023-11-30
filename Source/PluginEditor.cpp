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
    cutoffKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    cutoffKnob.setRange(20.0, 20000.0, 1.0);
    cutoffKnob.setValue(audioProcessor.getCutoffFrequency());
    addAndMakeVisible(&cutoffKnob);

    cutoffKnob.addListener(this);

    cutoffKnob.setValue(audioProcessor.getCutoffFrequency());

}

ModuFilterAudioProcessorEditor::~ModuFilterAudioProcessorEditor()
{
    cutoffKnob.removeListener(this);
}

//==============================================================================
void ModuFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ModuFilterAudioProcessorEditor::resized()
{
    cutoffKnob.setBounds(getLocalBounds().reduced(40));
}
