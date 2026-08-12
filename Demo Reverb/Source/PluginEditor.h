#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct ReverbSlider : juce::Slider // vertical bar slider, typical for classic reverb plugin style
{
    ReverbSlider() : juce::Slider(juce::Slider::SliderStyle::LinearBarVertical, juce::Slider::TextEntryBoxPosition::NoTextBox) {}
};

struct EqSlider : juce::Slider // rotery slider, typical for equalization
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
    std::vector<juce::Slider*> getReverbSliders();
    std::vector<juce::Slider*> getEqSliders();

    using apvts = juce::AudioProcessorValueTreeState;
    using Attachment = apvts::SliderAttachment;

    Attachment lowCutSliderAttachment,
        highCutSliderAttachment,
        roomSizeSliderAttachment,
        dampingSliderAttachment,
        dryLevelSliderAttachement,
        wetLevelSliderAttachment,
        widthSliderAttachment;

    // Colors definition
    juce::Colour const foregroundColor = juce::Colour::fromString("fff5f5f5");
    juce::Colour const backgroundColor = juce::Colour::fromString("ff202020");

    juce::Colour const sliderBackgroundColor = juce::Colour::fromString("ffe6e6e6");
    juce::Colour const roterySliderThumbColor = juce::Colour::fromString("ffd5d5d5");
    juce::Colour const reverbSliderTextBoxColor = juce::Colour::fromString("ff855d99");

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoReverbAudioProcessorEditor)
};
