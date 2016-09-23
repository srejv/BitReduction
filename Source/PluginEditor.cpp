/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ReducerAudioProcessorEditor::ReducerAudioProcessorEditor (ReducerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(bitDepth);
    bitDepth.setRange(1.0,32.0,1.0);
    bitDepth.setValue(32.0);
    bitDepth.addListener(this);
    
    addAndMakeVisible(bitRate);
    bitRate.setRange(1.0, 128000.0, 1.0);
    bitRate.setValue(2048.0);
    bitRate.addListener(this);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

ReducerAudioProcessorEditor::~ReducerAudioProcessorEditor()
{
}

//==============================================================================
void ReducerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void ReducerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    bitDepth.setBounds(area.removeFromTop(50));
    bitRate.setBounds(area.removeFromTop(50));
}
