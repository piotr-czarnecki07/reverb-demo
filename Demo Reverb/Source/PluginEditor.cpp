#include "PluginProcessor.h"
#include "PluginEditor.h"

std::vector<juce::Component*> DemoReverbAudioProcessorEditor::getReverbComponents()
{
    return {
        &roomSizeSlider,
        &dampingSlider,
        &dryLevelSlider,
        &wetLevelSlider,
        &widthSlider
    };
}

std::vector<juce::Component*> DemoReverbAudioProcessorEditor::getEqComponents()
{
    return {
        &lowCutSlider,
        &highCutSlider
    };
}

std::vector<juce::Slider*> DemoReverbAudioProcessorEditor::getReverbSliders()
{
    return {
        &roomSizeSlider,
        &dampingSlider,
        &dryLevelSlider,
        &wetLevelSlider,
        &widthSlider
    };
}

DemoReverbAudioProcessorEditor::DemoReverbAudioProcessorEditor (DemoReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    lowCutSliderAttachment(audioProcessor.apvts, "LowCut", lowCutSlider),
    highCutSliderAttachment(audioProcessor.apvts, "HighCut", highCutSlider),
    roomSizeSliderAttachment(audioProcessor.apvts, "RoomSize", roomSizeSlider),
    dampingSliderAttachment(audioProcessor.apvts, "Damping", dampingSlider),
    dryLevelSliderAttachement(audioProcessor.apvts, "DryLevel", dryLevelSlider),
    wetLevelSliderAttachment(audioProcessor.apvts, "WetLevel", wetLevelSlider),
    widthSliderAttachment(audioProcessor.apvts, "Width", widthSlider)
{
    setSize (500, 300);

    addAndMakeVisible(reverbSliderGroup);
    addAndMakeVisible(eqSliderGroup);

    for (auto* comp : getReverbComponents())
        reverbSliderGroup.addAndMakeVisible(comp);

    for (auto* comp : getEqComponents())
        eqSliderGroup.addAndMakeVisible(comp);

    reverbSliderGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colours::transparentBlack);
    eqSliderGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colours::transparentBlack);

    for (auto* slider : getReverbSliders()) {
        slider->setColour(juce::Slider::textBoxOutlineColourId, sliderBackgroundColor);

        slider->setColour(juce::Slider::thumbColourId, backgroundColor);
        slider->setColour(juce::Slider::trackColourId, sliderBackgroundColor);

        slider->setColour(juce::Slider::textBoxTextColourId, reverbSliderTextBoxColor);
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 10, 5);
    }
}

DemoReverbAudioProcessorEditor::~DemoReverbAudioProcessorEditor()
{
}

void DemoReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(backgroundColor);

    g.setColour(foregroundColor);
    g.setFont(47.0f);
    g.drawText("Reverbed", 20, 10, 460, 90, juce::Justification::centred);
}

void DemoReverbAudioProcessorEditor::resized()
{
    reverbSliderGroup.setBounds(20, 110, 460, 90);

    auto reverbArea = reverbSliderGroup.getLocalBounds();

    int w = reverbArea.getWidth() / 5;
    roomSizeSlider.setBounds(reverbArea.removeFromLeft(w).reduced(5));
    dampingSlider.setBounds(reverbArea.removeFromLeft(w).reduced(5));
    dryLevelSlider.setBounds(reverbArea.removeFromLeft(w).reduced(5));
    wetLevelSlider.setBounds(reverbArea.removeFromLeft(w).reduced(5));
    widthSlider.setBounds(reverbArea.reduced(5));

    eqSliderGroup.setBounds(20, 220, 460, 70);

    auto eqArea = eqSliderGroup.getLocalBounds();

    w = eqArea.getWidth() / 2;
    lowCutSlider.setBounds(eqArea.removeFromLeft(w).reduced(5));
    highCutSlider.setBounds(eqArea.reduced(5));
}
