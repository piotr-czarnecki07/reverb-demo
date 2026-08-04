#include "PluginProcessor.h"
#include "PluginEditor.h"

DemoReverbAudioProcessor::DemoReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DemoReverbAudioProcessor::~DemoReverbAudioProcessor()
{
}

const juce::String DemoReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DemoReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DemoReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DemoReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DemoReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DemoReverbAudioProcessor::getNumPrograms()
{
    return 1;
}

int DemoReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DemoReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DemoReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void DemoReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DemoReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void DemoReverbAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DemoReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DemoReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
}

bool DemoReverbAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* DemoReverbAudioProcessor::createEditor()
{
    return new DemoReverbAudioProcessorEditor (*this);
}

void DemoReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
}

void DemoReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DemoReverbAudioProcessor();
}
