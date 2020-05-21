/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"
# define M_PI           3.14159265358979323846  /* pi */
# define M_PI_2         1.57079632679489661923  /* pi/2 */
#include "signal.h"

//==============================================================================
TestFlangerAudioProcessor::TestFlangerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TestFlangerAudioProcessor::~TestFlangerAudioProcessor()
{
}

//==============================================================================
const String TestFlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestFlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestFlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestFlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TestFlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestFlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestFlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestFlangerAudioProcessor::setCurrentProgram (int index)
{
}

const String TestFlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void TestFlangerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TestFlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{   
    mSampleRate = sampleRate;
    delayBufLength = 100000;
    delayBufferL.setSize(getTotalNumOutputChannels(), delayBufLength);
    delayBufferR.setSize(getTotalNumOutputChannels(), delayBufLength);
    delayBufferL.clear();
    delayBufferR.clear();
    dpw = 1; //write index
    currentDelayL = 0.0;
    currentDelayR = 0.0;
    ph = 0.0;
    func_ = 0;
    frequency_ = 0.1;
    depth_ = 0.0;
    feedback_ = 0.0;
    sweepWidth_ = 0.0;
    invertedMode = 0;
}

void TestFlangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestFlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void TestFlangerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    int numSamples = buffer.getNumSamples();
    float* channelOutDataL = buffer.getWritePointer(0);
    float* channelOutDataR = buffer.getWritePointer(1);
    const float* channelInData = buffer.getReadPointer(0);
    
    
    for (int i = 0; i < numSamples; ++i)
    {
        float interpolatedSampleL = 0.0;
        float interpolatedSampleR = 0.0;

        if (invertedMode == 1) {
            depth_= -depth_;
        }

        if (func_ == 0) {
            //sinusoidal LFO function
            currentDelayL = sweepWidth_ * (0.5f + 0.5f * sinf(2.0 * M_PI * ph));                                               
            currentDelayR = sweepWidth_ * (0.5f + 0.5f * sinf(2.0 * M_PI * ph - M_PI_2));
        }
        else if (func_ == 1) {
            //triangular LFO function
            currentDelayL = sweepWidth_ * (0.5f + 0.5f * static_cast <float>(acos(sin(2 * M_PI* ph)) / M_PI_2));             
            currentDelayR = sweepWidth_ * (0.5f + 0.5f * static_cast <float>(acos(sin(2 * M_PI * ph - M_PI_2)) / M_PI_2)); 
        } 

        // Subtract 3 samples to the delay pointer to make sure we have enough previous samples to interpolate with
        float dprL = fmodf((float)dpw - (float)(currentDelayL * mSampleRate / 1000) + (float)delayBufLength - 3.0, (float)delayBufLength);
        float dprR = fmodf((float)dpw - (float)(currentDelayR * mSampleRate / 1000) + (float)delayBufLength - 3.0, (float)delayBufLength);

        // Use linear interpolation to read a fractional index into the buffer.
        float fractionL = dprL - floorf(dprL);
        float fractionR = dprR - floorf(dprR);
        int previousSampleL = (int)floorf(dprL);
        int previousSampleR = (int)floorf(dprR);
        int nextSampleL = (previousSampleL + 1) % delayBufLength;
        int nextSampleR = (previousSampleR + 1) % delayBufLength;

        interpolatedSampleL = fractionL * delayBufferL.getSample(0, nextSampleL) + (1.0f - fractionL) * delayBufferL.getSample(0, previousSampleL);
        interpolatedSampleR = fractionR * delayBufferR.getSample(0, nextSampleR) + (1.0f - fractionR) * delayBufferR.getSample(0, previousSampleR);
                
        delayBufferL.setSample(0, dpw, channelInData[i] + interpolatedSampleL * feedback_);
        delayBufferR.setSample(0, dpw, channelInData[i] + interpolatedSampleR * feedback_);

        channelOutDataL[i] = interpolatedSampleL * depth_ + channelInData[i] * (1 - depth_) ;
        channelOutDataR[i] = interpolatedSampleR * depth_ + channelInData[i] * (1 - depth_) ;

        if (++dpw >= delayBufLength)
            dpw = 0;

        ph += frequency_ * (1 / static_cast<float>( mSampleRate));
        if (ph >= 1.0)
            ph -= 1.0;
    }    
}

//==============================================================================
bool TestFlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestFlangerAudioProcessor::createEditor()
{
    return new TestFlangerAudioProcessorEditor (*this);
}

//==============================================================================
void TestFlangerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestFlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestFlangerAudioProcessor();
}
