#include "PluginProcessor.h"
#include "PluginEditor.h"

DemoReverbAudioProcessorEditor::DemoReverbAudioProcessorEditor (DemoReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

DemoReverbAudioProcessorEditor::~DemoReverbAudioProcessorEditor()
{
}

void DemoReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DemoReverbAudioProcessorEditor::resized()
{

}
