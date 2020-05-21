/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class TestFlangerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TestFlangerAudioProcessor();
    ~TestFlangerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float frequency_;           // Frequency of the LFO
    float sweepWidth_;          // Width of the LFO in samples
    float depth_;               // Amount of delayed signal mixed with original (0-1)
    float feedback_;            // Amount of feedback (>= 0, < 1)
    int func_;
    int invertedMode;
    
private:
    AudioSampleBuffer delayBufferL;
    AudioSampleBuffer delayBufferR;
   
    // Variables whose values are set externally:
    int mSampleRate{ 44100 };
    int numSamples;             // How many audio samples to process
    int delayBufLength;         // Length of our delay buffer in samples
    int dpw;                    // Write pointer into the delay buffer
    float ph;                   // Current LFO phase, always between 0-1
    float currentDelayL;
    float currentDelayR;    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestFlangerAudioProcessor)
};
