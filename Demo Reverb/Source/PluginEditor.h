#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DemoReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DemoReverbAudioProcessorEditor (DemoReverbAudioProcessor&);
    ~DemoReverbAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DemoReverbAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoReverbAudioProcessorEditor)
};
