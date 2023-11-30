/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ModuFilterAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    ModuFilterAudioProcessorEditor (ModuFilterAudioProcessor&);
    ~ModuFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider)
    {
        if (slider == &cutoffKnob)
        {
            audioProcessor.setCutoffFrequency(cutoffKnob.getValue());
        }
        else if (slider == &resonanceKnob)
        {
            audioProcessor.setResonance(resonanceKnob.getValue());
        }
    }

    void filterTypeButtonClicked()
    {
        auto type = audioProcessor.getFilterType();
        type = static_cast<ModuFilterAudioProcessor::FilterType>((type + 1) % 3);

        audioProcessor.setFilterType(type);

        switch (type)
        {
        case ModuFilterAudioProcessor::LowPass:  filterTypeButton.setButtonText("Filter Type: LowPass"); break;
        case ModuFilterAudioProcessor::HighPass: filterTypeButton.setButtonText("Filter Type: HighPass"); break;
        case ModuFilterAudioProcessor::BandPass: filterTypeButton.setButtonText("Filter Type: BandPass"); break;
        }
    }

    void ModuFilterAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
    {
        if (parameterID == "cutoff")
        {
            cutoffKnob.setValue(newValue, juce::dontSendNotification);
        }
        else if (parameterID == "resonance")
        {
            resonanceKnob.setValue(newValue, juce::dontSendNotification);
        }
        else if (parameterID == "filterType")
        {
            filterTypeButton.setToggleState(static_cast<bool>(newValue), juce::dontSendNotification);
        }
    }


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ModuFilterAudioProcessor& audioProcessor;
    juce::Slider cutoffKnob;
    juce::Slider resonanceKnob;
    juce::TextButton filterTypeButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filterTypeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuFilterAudioProcessorEditor)
};
