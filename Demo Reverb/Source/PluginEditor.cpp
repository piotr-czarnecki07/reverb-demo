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

std::vector<juce::Slider*> DemoReverbAudioProcessorEditor::getEqSliders()
{
    return {
        &lowCutSlider,
        &highCutSlider
    };
}

std::vector<juce::Label*> DemoReverbAudioProcessorEditor::getReverbLabels()
{
    return {
        &roomSizeLabel,
        &dampingLabel,
        &dryLevelLabel,
        &wetLevelLabel,
        &widthLabel
    };
}

std::vector<juce::Label*> DemoReverbAudioProcessorEditor::getEqLabels()
{
    return {
        &lowCutLabel,
        &highCutLabel
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

    // Reverb and Eq sliders settings
    addAndMakeVisible(reverbSliderGroup);
    addAndMakeVisible(eqSliderGroup);

    for (auto* comp : getReverbComponents())
        reverbSliderGroup.addAndMakeVisible(comp);

    for (auto* comp : getEqComponents())
        eqSliderGroup.addAndMakeVisible(comp);

    reverbSliderGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colours::transparentBlack);
    eqSliderGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colours::transparentBlack);

    for (auto* slider : getReverbSliders()) {
        slider->setColour(juce::Slider::textBoxOutlineColourId, sliderBackgroundColor); // ramka

        slider->setColour(juce::Slider::thumbColourId, backgroundColor); // wolny obszar
        slider->setColour(juce::Slider::trackColourId, sliderBackgroundColor); // zakreslony obszar

        slider->setColour(juce::Slider::textBoxTextColourId, reverbSliderTextBoxColor);
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 10, 5);
    }

    for (auto* slider : getEqSliders()) {
        slider->setColour(juce::Slider::thumbColourId, roterySliderThumbColor); // pokrętło
        slider->setColour(juce::Slider::rotarySliderFillColourId, foregroundColor); // zakreślony obszar (obecny)

        slider->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black); // rotery background (niezaznaczony obszar)

        slider->setColour(juce::Slider::textBoxTextColourId, foregroundColor);
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    }

    // Labels settings
    addAndMakeVisible(reverbLabelGroup);
    addAndMakeVisible(eqLabelGroup);

    for (auto* label : getReverbLabels()) {
        reverbLabelGroup.addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::centred);
    }

    for (auto* label : getEqLabels()) {
        eqLabelGroup.addAndMakeVisible(label);
        label->setJustificationType(juce::Justification::centred);
    }

    reverbLabelGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colours::transparentBlack);
    eqLabelGroup.setColour(juce::GroupComponent::outlineColourId, juce::Colours::transparentBlack);

    roomSizeLabel.setText("Room", juce::NotificationType::dontSendNotification);
    dampingLabel.setText("Damping", juce::NotificationType::dontSendNotification);
    dryLevelLabel.setText("Dry", juce::NotificationType::dontSendNotification);
    wetLevelLabel.setText("Wet", juce::NotificationType::dontSendNotification);
    widthLabel.setText("Width", juce::NotificationType::dontSendNotification);

    lowCutLabel.setText("Low Cut", juce::NotificationType::dontSendNotification);
    highCutLabel.setText("High Cut", juce::NotificationType::dontSendNotification);
}

DemoReverbAudioProcessorEditor::~DemoReverbAudioProcessorEditor()
{
}

void DemoReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(backgroundColor);

    g.setColour(foregroundColor);
    g.setFont(47.0f);
    g.drawText("Reverbed", 20, 10, 460, 50, juce::Justification::centred);
}

void DemoReverbAudioProcessorEditor::resized()
{
    // reverb sliders placement
    reverbSliderGroup.setBounds(20, 90, 460, 90);
    auto reverbSliderArea = reverbSliderGroup.getLocalBounds();

    int w = reverbSliderArea.getWidth() / 5;

    for (auto* slider : getReverbSliders()) {
        auto slot = reverbSliderArea.removeFromLeft(w);
        slider->setBounds(slot.withSizeKeepingCentre(50, slot.getHeight()));
    }

    // reverb labels
    reverbLabelGroup.setBounds(20, 180, 460, 25);
    auto reverbLabelArea = reverbLabelGroup.getLocalBounds();

    roomSizeLabel.setBounds(reverbLabelArea.removeFromLeft(w).reduced(5));
    dampingLabel.setBounds(reverbLabelArea.removeFromLeft(w).reduced(5));
    dryLevelLabel.setBounds(reverbLabelArea.removeFromLeft(w).reduced(5));
    wetLevelLabel.setBounds(reverbLabelArea.removeFromLeft(w).reduced(5));
    widthLabel.setBounds(reverbLabelArea.reduced(5));

    // eq text labels
    eqLabelGroup.setBounds(20, 210, 460, 25);
    auto eqLabelArea = eqLabelGroup.getLocalBounds();

    w = eqLabelArea.getWidth() / 2;

    lowCutLabel.setBounds(eqLabelArea.removeFromLeft(w).reduced(5));
    highCutLabel.setBounds(eqLabelArea.reduced(5));

    // eq sliders placement
    eqSliderGroup.setBounds(20, 220, 460, 70);
    auto eqSliderArea = eqSliderGroup.getLocalBounds();

    lowCutSlider.setBounds(eqSliderArea.removeFromLeft(w).reduced(5));
    highCutSlider.setBounds(eqSliderArea.reduced(5));
}
