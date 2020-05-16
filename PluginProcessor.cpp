/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    
    delayBufLength = 100000;
    
    dpw = 0; //write index
    //write init value for sliders?
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
    ScopedNoDenormals noDenormals;
    
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    


    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    //********************************************************************************************//
    // 3) Delay line implementation
    for (int i = 0; i < numSamples; ++i){
    const float in = channelData[i];
    float interpolatedSample = 0.0;
    // Recalculate the read pointer position with respect to
    // the write pointer.
    float currentDelay = sweepWidth_ * (0.5f + 0.5f * sinf(2.0 * 3.14 * ph));
    // Subtract 3 samples to the delay pointer to make sure
    // we have enough previous samples to interpolate with
    float dpr = fmodf((float)dpw - (float)(currentDelay * getSampleRate()) + (float)delayBufLength - 3.0, (float)delayBufLength);
    // Use linear interpolation to read a fractional index
    // into the buffer.
    float fraction = dpr - floorf(dpr);
    int previousSample = (int)floorf(dpr);
    int nextSample = (previousSample + 1) % delayBufLength;
    interpolatedSample = fraction*delayData[nextSample] + (1.0f-fraction)*delayData[previousSample];
    // Store the current information in the delay buffer.
    // With feedback, what we read is included in what gets
    // stored in the buffer, otherwise it’s just a simple
    // delay line of the input signal.
    delayData[dpw] = in + (interpolatedSample * feedback_);
    // Increment the write pointer at a constant rate.
    if (++dpw >= delayBufLength)
    dpw = 0;
    // Store the output in the buffer, replacing the input
    channelData[i] = in + depth_ * interpolatedSample;
    // Update the LFO phase, keeping it in the range 0-1
    ph += frequency_*inverseSampleRate;
    if(ph >= 1.0)
    ph -= 1.0;
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
