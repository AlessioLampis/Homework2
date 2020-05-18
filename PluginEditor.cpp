/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestFlangerAudioProcessorEditor::TestFlangerAudioProcessorEditor(TestFlangerAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // FREQUENCY
    FrequencySlider.setSliderStyle (Slider::SliderStyle::Rotary);
    FrequencySlider.setRange (100.0f, 10000.0f, 10.0f);
    FrequencySlider.setTextBoxStyle (Slider::TextBoxAbove, true, 100, 20);
    FrequencySlider.addListener(this);
    FrequencySlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FrequencyLabel.setFont(10.0f);
    FrequencyLabel.setText ("LFO frequency", dontSendNotification);
    FrequencyLabel.setJustificationType(Justification::centredBottom);
    FrequencyLabel.attachToComponent(&FrequencySlider, false);

    addAndMakeVisible (FrequencySlider);
    addAndMakeVisible (FrequencyLabel);

    // SWEEP WIDTH
    SweepWidthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    SweepWidthSlider.setRange (0.0, 1.0, 0.01F);
    SweepWidthSlider.setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    SweepWidthSlider.addListener(this);
    SweepWidthSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    SweepWidthLabel.setText ("Sweep", dontSendNotification);
    SweepWidthLabel.setJustificationType(Justification::centredBottom);
    SweepWidthLabel.attachToComponent(&SweepWidthSlider, false);

    addAndMakeVisible (SweepWidthSlider);
    addAndMakeVisible (SweepWidthLabel);
    
    //DEPTH SLIDER
    DepthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    DepthSlider.setRange (0.0, 1.0);
    DepthSlider.setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    DepthSlider.addListener(this);
    DepthSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    DepthLabel.setText ("Depth", dontSendNotification);
    DepthLabel.setJustificationType(Justification::centredBottom);
    DepthLabel.attachToComponent(&DepthSlider, false);

    
    addAndMakeVisible (DepthSlider);
    addAndMakeVisible (DepthLabel);
    
    //FEEDBACK SLIDER
    FeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FeedbackSlider.setRange (0.0, 1.0);
    FeedbackSlider.setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    FeedbackSlider.addListener(this);
    FeedbackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FeedbackLabel.setText ("Feedback", dontSendNotification);
    FeedbackLabel.setJustificationType(Justification::centredBottom);
    FeedbackLabel.attachToComponent(&FeedbackSlider, false);
    
    addAndMakeVisible (FeedbackSlider);
    addAndMakeVisible (FeedbackLabel);

    //FUNC SLIDER
    FuncSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FuncSlider.setRange(0.0, 3.0, 1.0f);
    FuncSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 50, 20);
    FuncSlider.addListener(this);
    FuncSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FuncLabel.setText("Waveform", dontSendNotification);
    FuncLabel.setJustificationType(Justification::centredBottom);
    FuncLabel.attachToComponent(&FuncSlider, false);


    addAndMakeVisible(FuncSlider);
    addAndMakeVisible(FuncLabel);

    setSize (800, 500);
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
    g.drawFittedText ("Flanger", getLocalBounds(), Justification::centredTop, 12);
}

void TestFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const auto startY = 0.45f;
    const auto startX = 0.45f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.2f;

    FrequencySlider.setBoundsRelative (startX + dialWidth*3, startY + 0.1f, dialWidth, dialHeight);
    
    SweepWidthSlider.setBoundsRelative(startX + dialWidth *3, startY - 0.1f, dialWidth, dialHeight);
    
    DepthSlider.setBoundsRelative(startX - dialWidth * 3, startY - 0.1f, dialWidth, dialHeight);
    
    FeedbackSlider.setBoundsRelative (startX, startY, dialWidth, dialHeight);

    FuncSlider.setBoundsRelative(startX - dialWidth* 3, startY + 0.1f, dialWidth, dialHeight);
}

void TestFlangerAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &FrequencySlider)
        processor.set_freq(FrequencySlider.getValue());
    else if (slider == &SweepWidthSlider)
        processor.set_sweep(SweepWidthSlider.getValue());
    else if (slider == &DepthSlider)
        processor.set_depth(DepthSlider.getValue());
    else if (slider == &FeedbackSlider)
        processor.set_feedback(FeedbackSlider.getValue());
    else if (slider== &FuncSlider)
        processor.set_feedback(FuncSlider.getValue());
}
