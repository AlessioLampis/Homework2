/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TestFlangerAudioProcessorEditor  : public AudioProcessorEditor,  private Slider::Listener
{
public:
    TestFlangerAudioProcessorEditor (TestFlangerAudioProcessor&);
    ~TestFlangerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestFlangerAudioProcessor& processor;
    
    Slider FrequencySlider;
    Label FrequencyLabel;

    Slider SweepWidthSlider;
    Label SweepWidthLabel;

    Slider DepthSlider;
    Label DepthLabel;

    Slider FeedbackSlider;
    Label FeedbackLabel;

    Slider FuncSlider;
    Label FuncLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestFlangerAudioProcessorEditor);
};
