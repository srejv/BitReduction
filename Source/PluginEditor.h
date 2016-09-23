/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class ReducerAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    ReducerAudioProcessorEditor (ReducerAudioProcessor&);
    ~ReducerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &bitDepth) {
            processor.setBitsToUse(bitDepth.getValue());
        }
        if(slider == &bitRate) {
            processor.setBitRate(bitRate.getValue());
        }
    };
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReducerAudioProcessor& processor;

    Slider bitDepth;
    Slider bitRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReducerAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
