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
    //FREQUENCY SLIDER ADDED GUI
    FrequencySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FrequencySlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FrequencyLabel.attachToComponent(&FrequencySlider, false);
    FrequencyLabel.setFont(10.0f);

    FrequencySlider.setRange (0.1f, 10.0f, 0.1f);
    FrequencySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    FrequencySlider.addListener(this);
    FrequencyLabel.setText ("LFO freq", dontSendNotification);
    FrequencyLabel.setColour(Label::textColourId, Colours::black);
    FrequencySlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);

    addAndMakeVisible (FrequencySlider);
    addAndMakeVisible (FrequencyLabel);
    
    //SWEEP WIDTH SLIDER ADDED GUI
    SweepWidthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    SweepWidthSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    SweepWidthLabel.setJustificationType(Justification::centredBottom);
    SweepWidthLabel.attachToComponent(&SweepWidthSlider, false);

    SweepWidthSlider.setRange (0.0f, 1.0f, 0.01f);
    SweepWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    SweepWidthSlider.addListener(this);
    SweepWidthLabel.setText ("Sweep", dontSendNotification);
    SweepWidthLabel.setColour(Label::textColourId, Colours::black);
    SweepWidthSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);

    addAndMakeVisible (SweepWidthSlider);
    addAndMakeVisible (SweepWidthLabel);
    
    //DEPTH SLIDER ADDED GUI
    DepthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    DepthSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    DepthLabel.setJustificationType(Justification::centredBottom);
    DepthLabel.attachToComponent(&DepthSlider, false);

    DepthSlider.setRange (0.0f, 1.0f);
    DepthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    DepthSlider.addListener(this);
    DepthLabel.setText ("Depth", dontSendNotification);
    DepthLabel.setColour(Label::textColourId, Colours::black);
    DepthSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);

    addAndMakeVisible (DepthSlider);
    addAndMakeVisible (DepthLabel);
    
    // FEEDBACK SLIDER ADDED GUI
    FeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FeedbackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FeedbackLabel.setJustificationType(Justification::centredBottom);
    FeedbackLabel.attachToComponent(&FeedbackSlider, false);

    FeedbackSlider.setRange (0.0f, 1.0f);
    FeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    FeedbackSlider.addListener(this);
    FeedbackLabel.setText ("Feedback", dontSendNotification);
    FeedbackLabel.setColour(Label::textColourId, Colours::black);
    FeedbackSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);

    addAndMakeVisible (FeedbackSlider);
    addAndMakeVisible (FeedbackLabel);

    //FUNC SLIDER ADDED GUI
    FuncSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FuncSlider.setRange(0.0, 3.0, 1.0f);
    FuncSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    FuncSlider.addListener(this);
    FuncSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FuncLabel.setText("Waveform", dontSendNotification);
    FuncLabel.setJustificationType(Justification::centredBottom);
    FuncLabel.attachToComponent(&FuncSlider, false);
    FuncLabel.setColour(Label::textColourId, Colours::black);
    FuncSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);


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
    g.fillAll (Colours::white); //fill all the element with white
    g.setColour (Colours::black); //setting the colour for future drawing
    g.setFont(Font("Felix Titling", 50.0f, Font::bold));
    g.drawFittedText ("Flanger", 250, 100 , 300, 40, Justification::centredTop, 12);
}

void TestFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const auto startY = 0.45f;
    const auto startX = 0.45f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.2f;

    FrequencySlider.setBoundsRelative(startX + dialWidth * 3, startY + 0.1f, dialWidth, dialHeight);

    SweepWidthSlider.setBoundsRelative(startX + dialWidth * 3, startY - 0.2f, dialWidth, dialHeight);

    DepthSlider.setBoundsRelative(startX - dialWidth * 3, startY - 0.2f, dialWidth, dialHeight);

    FeedbackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);

    FuncSlider.setBoundsRelative(startX - dialWidth * 3, startY + 0.1f, dialWidth, dialHeight);
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
    else if (slider == &FuncSlider)
        processor.set_feedback(FuncSlider.getValue());
}

