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

    juce::AudioProcessorValueTreeState parameters;
    static juce::AudioProcessorValueTreeState::ParameterLayout createParams();

    juce::AudioProcessorValueTreeState& getParameters()
    {
        return parameters;
    }



    enum FilterType
    {
        LowPass,
        HighPass,
        BandPass
    };




    void ModuFilterAudioProcessor::setFilterType(FilterType newType)
    {
        currentFilterType = newType;
        updateFilter();
    }

    void updateFilter()
    {
        for (auto& filter : filters)
        {
            switch (currentFilterType)
            {
            case LowPass:
                filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), cutoffFrequency, resonance);
                break;
            case HighPass:
                filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), cutoffFrequency, resonance);
                break;
            case BandPass:
                filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), cutoffFrequency, resonance);
                break;
            }
        }
    }

    void setCutoffFrequency(float newCutoffFrequency)
    {
        cutoffFrequency = newCutoffFrequency;
        updateFilter();
    }
    void setResonance(float newResonance)
    {
        resonance = newResonance;
        updateFilter();
    }



    float getCutoffFrequency() const { return cutoffFrequency; }
    float getResonance() const { return resonance; }
    FilterType getFilterType() const { return currentFilterType; }

private:

    juce::dsp::IIR::Filter<float> filters[2];
    float cutoffFrequency = 1000.0f;
    float resonance = 1.0f;
    FilterType currentFilterType = LowPass;



    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuFilterAudioProcessor)
};
