#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct ReverbSlider : juce::Slider // vertical bar slider, typical for classic reverb plugin style
{
    ReverbSlider() : juce::Slider(juce::Slider::SliderStyle::LinearBarVertical, juce::Slider::TextEntryBoxPosition::NoTextBox) {}
};

struct EqSlider : juce::Slider
{
    EqSlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox) {}
};

class DemoReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DemoReverbAudioProcessorEditor (DemoReverbAudioProcessor&);
    ~DemoReverbAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DemoReverbAudioProcessor& audioProcessor;

    juce::GroupComponent reverbSliderGroup,
        eqSliderGroup;

    EqSlider lowCutSlider,
        highCutSlider;
    
    ReverbSlider roomSizeSlider,
        dampingSlider,
        dryLevelSlider,
        wetLevelSlider,
        widthSlider;

    std::vector<juce::Component*> getReverbComponents();
    std::vector<juce::Component*> getEqComponents();

    using apvts = juce::AudioProcessorValueTreeState;
    using Attachment = apvts::SliderAttachment;

    Attachment lowCutSliderAttachment,
        highCutSliderAttachment,
        roomSizeSliderAttachment,
        dampingSliderAttachment,
        dryLevelSliderAttachement,
        wetLevelSliderAttachment,
        widthSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoReverbAudioProcessorEditor)
};
