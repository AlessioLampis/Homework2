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
    
    void set_freq(float val);
    void set_sweep(float val);
    void set_depth(int val);
    void set_feedback(int val);
    void set_func(int val);

    float frequency_; // Frequency of the LFO
    float sweepWidth_; // Width of the LFO in samples
    float depth_; // Amount of delayed signal mixed with
    // original (0-1)
    float feedback_; // Amount of feedback (>= 0, < 1)
    float func_; //waveform of the LFO
private:
    AudioSampleBuffer delayBuffer;
    //==============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestFlangerAudioProcessor)

 
    // Variables whose values are set externally:
    int mSampleRate{ 44100 };
    int numSamples; // How many audio samples to process
    float *channelData; // Array of samples, length numSamples
    float *delayData; // Our own circular buffer of samples
    int delayBufLength; // Length of our delay buffer in samples
    int dpw; // Write pointer into the delay buffer
    int dpr;
    int pr;
    float ph; // Current LFO phase, always between 0-1
    float inverseSampleRate; // 1/f_s, where f_s = sample rate
    
    // User-adjustable effect parameters:

    //********************************************************************************************//

    
};
