/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ReducerAudioProcessor::ReducerAudioProcessor()
{
}

ReducerAudioProcessor::~ReducerAudioProcessor()
{
}

//==============================================================================
const String ReducerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReducerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReducerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double ReducerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReducerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReducerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReducerAudioProcessor::setCurrentProgram (int index)
{
}

const String ReducerAudioProcessor::getProgramName (int index)
{
    return String();
}

void ReducerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ReducerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mySampleRate = sampleRate;
}

void ReducerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReducerAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif


// double bitsToUse (bit reduction), mySampleRate (the sample rate of your DAW), bitRate (sample rate reduction) in the header file.
#define ROUND(f) ((float)((f > 0.0) ? floor(f + 0.5) : ceil(f - 0.5)))

void ReducerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    
    int max = std::pow(2, bitsToUse) - 1;
    int step = mySampleRate / bitRate;
    if(step < 1) step = 1;
 
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        int i = 0;
        while (i < buffer.getNumSamples())
        {
            float sample = ROUND((channelData[i] + 1.0f) * max) / max - 1.0f;
 
            // this loop causes us to simulate a down-sample to a lower sample rate
            for (int j = 0; j < step && i < buffer.getNumSamples(); j++, i++)
            {
                channelData[i] = sample;
            }
        }
    }
}

//==============================================================================
bool ReducerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ReducerAudioProcessor::createEditor()
{
    return new ReducerAudioProcessorEditor (*this);
}

//==============================================================================
void ReducerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReducerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReducerAudioProcessor();
}
