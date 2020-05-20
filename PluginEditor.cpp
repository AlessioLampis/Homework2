/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestFlangerAudioProcessorEditor::TestFlangerAudioProcessorEditor (TestFlangerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    FrequencySlider.setRange (0.1f, 10.0f, 0.1f);
    FrequencySlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
    FrequencySlider.addListener(this);
    FrequencyLabel.setText ("LFO frequency", dontSendNotification);
    
    addAndMakeVisible (FrequencySlider);
    addAndMakeVisible (FrequencyLabel);
    
    SweepWidthSlider.setRange (0.0f, 1.0f, 0.01f);
    SweepWidthSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
    SweepWidthSlider.addListener(this);
    SweepWidthLabel.setText ("Sweep", dontSendNotification);
    
    addAndMakeVisible (SweepWidthSlider);
    addAndMakeVisible (SweepWidthLabel);
    
    DepthSlider.setRange (0.0f, 1.0f);
    DepthSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
    DepthSlider.addListener(this);
    DepthLabel.setText ("Depth", dontSendNotification);
    
    addAndMakeVisible (DepthSlider);
    addAndMakeVisible (DepthLabel);
    
    FeedbackSlider.setRange (0.0f, 1.0f);
    FeedbackSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
    FeedbackSlider.addListener(this);
    FeedbackLabel.setText ("Feedback", dontSendNotification);
    
    addAndMakeVisible (FeedbackSlider);
    addAndMakeVisible (FeedbackLabel);
    
    setSize (400, 300);
}

TestFlangerAudioProcessorEditor::~TestFlangerAudioProcessorEditor()
{
}

//==============================================================================
void TestFlangerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("Flanger Effect", getLocalBounds(), Justification::centredTop, 12);
}

void TestFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    FrequencyLabel.setBounds (10, 40, 90, 20);
    FrequencySlider.setBounds (100, 40, getWidth() - 110, 20);
    
    SweepWidthLabel.setBounds (10, 80, 90, 20);
    SweepWidthSlider.setBounds (100, 80, getWidth() - 110, 20);
    
    DepthLabel.setBounds (10, 120, 90, 20);
    DepthSlider.setBounds (100, 120, getWidth() - 110, 20);
    
    FeedbackLabel.setBounds (10, 160, 90, 20);
    FeedbackSlider.setBounds (100, 160, getWidth() - 110, 20);
}

void TestFlangerAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &FrequencySlider)
        processor.frequency_ = FrequencySlider.getValue();
    else if (slider == &SweepWidthSlider)
        processor.sweepWidth_ = SweepWidthSlider.getValue();
    else if (slider == &DepthSlider)
        processor.set_depth(DepthSlider.getValue());
    else if (slider == &FeedbackSlider)
        processor.set_feedback(FeedbackSlider.getValue());
}

