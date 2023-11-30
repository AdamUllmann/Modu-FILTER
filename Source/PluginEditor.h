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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ModuFilterAudioProcessor& audioProcessor;
    juce::Slider cutoffKnob;
    juce::Slider resonanceKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuFilterAudioProcessorEditor)
};
