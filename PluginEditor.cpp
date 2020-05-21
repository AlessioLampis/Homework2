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
    //FREQUENCY SLIDER ADDED GUI
    FrequencySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FrequencySlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FrequencyLabel.attachToComponent(&FrequencySlider, false);
    FrequencyLabel.setFont(10.0f);

    FrequencySlider.setRange(0.10f, 10.00f, 0.01f);
    FrequencySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    FrequencySlider.addListener(this);
    FrequencyLabel.setText("LFO freq", dontSendNotification);
    FrequencyLabel.setColour(Label::textColourId, Colours::black);
    FrequencySlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    FrequencySlider.setValue(4.95f);
    addAndMakeVisible(FrequencySlider);
    addAndMakeVisible(FrequencyLabel);

    
    //SWEEP WIDTH SLIDER ADDED GUI
    SweepWidthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    SweepWidthSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    SweepWidthLabel.setJustificationType(Justification::centredBottom);
    SweepWidthLabel.attachToComponent(&SweepWidthSlider, false);
    SweepWidthSlider.setRange(0.00f, 1.00f, 0.01f);
    SweepWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    SweepWidthSlider.addListener(this);
    SweepWidthLabel.setText("Sweep", dontSendNotification);
    SweepWidthLabel.setColour(Label::textColourId, Colours::black);
    SweepWidthSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    SweepWidthSlider.setValue(0.5f);

    addAndMakeVisible(SweepWidthSlider);
    addAndMakeVisible(SweepWidthLabel);

    
    //DEPTH SLIDER ADDED GUI
    DepthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    DepthSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    DepthLabel.setJustificationType(Justification::centredBottom);
    DepthLabel.attachToComponent(&DepthSlider, false);

    DepthSlider.setRange(0.0f, 1.0f, 0.1f);
    DepthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    DepthSlider.addListener(this);
    DepthLabel.setText("Depth", dontSendNotification);
    DepthLabel.setColour(Label::textColourId, Colours::black);
    DepthSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    DepthSlider.setValue(0.5f);

    addAndMakeVisible(DepthSlider);
    addAndMakeVisible(DepthLabel);


    // FEEDBACK SLIDER ADDED GUI
    FeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FeedbackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    FeedbackLabel.setJustificationType(Justification::centredBottom);
    FeedbackLabel.attachToComponent(&FeedbackSlider, false);

    FeedbackSlider.setRange(0.00f, 0.95f, 0.01f);
    FeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    FeedbackSlider.addListener(this);
    FeedbackLabel.setText("Feedback", dontSendNotification);
    FeedbackLabel.setColour(Label::textColourId, Colours::black);
    FeedbackSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
    FeedbackSlider.setValue(0.475f);

    addAndMakeVisible(FeedbackSlider);
    addAndMakeVisible(FeedbackLabel);


    //FUNC SLIDER ADDED GUI
    FuncSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    FuncSlider.setRange(0, 1, 1);
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

    //INVERTED MODE SLIDER ADDED GUI
    InvertedSlider.setRange(0, 1, 1);
    InvertedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    InvertedSlider.addListener(this);
    InvertedSlider.setColour(Slider::ColourIds::thumbColourId, Colours::greenyellow);
    InvertedLabel.attachToComponent(&InvertedSlider, false);
    InvertedLabel.setColour(Label::textColourId, Colours::black);
    InvertedLabel.setText("Iverted", dontSendNotification);
    InvertedLabel.setJustificationType(Justification::centredBottom);
    InvertedSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::white);
    InvertedSlider.setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::white);

    addAndMakeVisible(InvertedSlider);
    addAndMakeVisible(InvertedLabel);
    
    setSize (800, 500);
}

TestFlangerAudioProcessorEditor::~TestFlangerAudioProcessorEditor()
{
}

//==============================================================================
void TestFlangerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::white); //fill all the element with white
    g.setColour(Colours::black); //setting the colour for future drawing
    g.setFont(Font("Felix Titling", 50.0f, Font::bold));
    g.drawFittedText("Flanger", 250, 100, 300, 40, Justification::centredTop, 12);
}

void TestFlangerAudioProcessorEditor::resized()
{
    const auto startY = 0.45f;
    const auto startX = 0.45f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.2f;

    FrequencySlider.setBoundsRelative(startX + dialWidth * 3, startY + 0.1f, dialWidth, dialHeight);

    SweepWidthSlider.setBoundsRelative(startX + dialWidth * 3, startY - 0.2f, dialWidth, dialHeight);

    DepthSlider.setBoundsRelative(startX - dialWidth * 3, startY - 0.2f, dialWidth, dialHeight);

    FeedbackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);

    FuncSlider.setBoundsRelative(startX - dialWidth * 3, startY + 0.1f, dialWidth, dialHeight);

    InvertedLabel.setBoundsRelative(startX, startY + 0.25f, dialWidth, dialHeight -0.1f );
    InvertedSlider.setBoundsRelative(startX, startY + 0.25f, dialWidth, dialHeight -0.1f );
}

void TestFlangerAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &FrequencySlider)
        processor.frequency_ = FrequencySlider.getValue();
    else if (slider == &SweepWidthSlider)
        processor.sweepWidth_ = SweepWidthSlider.getValue();
    else if (slider == &DepthSlider)
        processor.depth_ = DepthSlider.getValue();
    else if (slider == &FeedbackSlider)
        processor.feedback_ = FeedbackSlider.getValue();
    else if (slider == &FuncSlider)
        processor.func_ = FuncSlider.getValue();
    else if (slider == &InvertedSlider)
        processor.invertedMode = InvertedSlider.getValue();
}

