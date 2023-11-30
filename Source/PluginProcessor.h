/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class ModuFilterAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ModuFilterAudioProcessor();
    ~ModuFilterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;



    void ModuFilterAudioProcessor::setCutoffFrequency(float newCutoffFrequency)
    {
        cutoffFrequency = newCutoffFrequency;
        for (auto& filter : lowpassFilters)
        {
            filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), cutoffFrequency);
        }
    }

    float getCutoffFrequency() const { return cutoffFrequency; }


private:

    juce::dsp::IIR::Filter<float> lowpassFilters[2];
    float cutoffFrequency = 1000.0f;



    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuFilterAudioProcessor)
};
