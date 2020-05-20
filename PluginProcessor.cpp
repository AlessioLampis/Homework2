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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    //********************************************************************************************//
    // 2) Initialize the variables that we are going to need in processBlock function: 
    // the buffer, the write and read pointer, the delay value
    
    mSampleRate = sampleRate;
    delayBufLength = 100000;
    delayBuffer.setSize(getTotalNumOutputChannels(), delayBufLength);
    dpr = delayBufLength/2;
    dpw = 1; //write index
    pr = delayBufLength / 2;
    //********************************************************************************************//

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
        float currentDelay = 5000 * sweepWidth_ * (sinf(2.0 * M_PI * frequency_));

        if (++dpw >= delayBufLength)
            dpw = 0;
        if (++dpr >= delayBufLength)
            dpr = 0;
        if (currentDelay > delayBufLength / 2 - 1)
            currentDelay = delayBufLength / 2 - 1;
        if (currentDelay < -(delayBufLength / 2 - 1))
            currentDelay = -(delayBufLength / 2 - 1);
        pr = dpr + currentDelay;
        if (pr >= delayBufLength)
            pr -= delayBufLength;
        if (pr < 0)
            pr += delayBufLength;

        delayBuffer.setSample(0, dpw, channelInData[i]);
        float sampleFlange = delayBuffer.getSample(0, pr);
        float sampleDirect = delayBuffer.getSample(0, dpr);
        channelOutDataL[i] = sampleFlange + sampleDirect ;
        channelOutDataR[i] = sampleFlange + sampleDirect ;
    }
    //********************************************************************************************//

    
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

//==============================================================================
// This creates new instances of the plugin..

void TestFlangerAudioProcessor::set_freq(float val)
{
    frequency_ = val;
}
void TestFlangerAudioProcessor::set_sweep(float val)
{
    sweepWidth_ = val;
}
void TestFlangerAudioProcessor::set_depth(int val)
{
    depth_ = val;
}
void TestFlangerAudioProcessor::set_feedback(int val)
{
    feedback_ = val;
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestFlangerAudioProcessor();
}
