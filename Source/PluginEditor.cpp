/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace {
    const float KEY_HEIGHT = 80.0f;
    const float KEY_WIDTH = 32.0f;
    const int PANEL_MARGIN = 2;
}

//==============================================================================
TinySynthAudioProcessorEditor::TinySynthAudioProcessorEditor (TinySynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
    , keyboardComponent(p.getKeyboardState(), MidiKeyboardComponent::Orientation::horizontalKeyboard)
    , oscParamsComponent(&p.oscParameters)
    , ampEnvParamsComponent(&p.ampEnvParameters)
    , lfoParamsComponent(&p.lfoParameters)
    , filterParamsComponent(&p.filterParameters)
    , reverbParamsComponent(&p.reverbParameters)
    , driveParamsComponent(p.driveParameter)
    , miscParamsComponent(p.masterVolumePrameter, p.voiceSizeParameter, p.velocitySenseParameter)
    , scopeComponent(p.getAudioBufferQueue())
{
    keyboardComponent.setKeyWidth(KEY_WIDTH);

    addAndMakeVisible(keyboardComponent);
    addAndMakeVisible(oscParamsComponent);
    addAndMakeVisible(ampEnvParamsComponent);
    addAndMakeVisible(lfoParamsComponent);
    addAndMakeVisible(filterParamsComponent);
    addAndMakeVisible(driveParamsComponent);
    addAndMakeVisible(reverbParamsComponent);
    addAndMakeVisible(miscParamsComponent);
    addAndMakeVisible(scopeComponent);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(960, 540 + KEY_HEIGHT);

    // assign custom look and feel.
    customLookAndFeel = new LookAndFeel_V4(LookAndFeel_V4::getMidnightColourScheme());

    customLookAndFeel->setColour(TooltipWindow::ColourIds::textColourId, Colours::white);
    customLookAndFeel->setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::mediumvioletred);
    customLookAndFeel->setColour(Slider::ColourIds::trackColourId, Colours::yellow);

    for (Component* child : getChildren()) {
        child->setLookAndFeel(customLookAndFeel);
    }
}

TinySynthAudioProcessorEditor::~TinySynthAudioProcessorEditor()
{
    for (Component* child : getChildren()) {
        child->setLookAndFeel(nullptr);
    }

    delete customLookAndFeel;
}

//==============================================================================
void TinySynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
#if 0
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
#endif

    g.fillAll(Colours::black);

}

void TinySynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    Rectangle<int> bounds = getLocalBounds();

    keyboardComponent.setBounds(bounds.removeFromBottom(KEY_HEIGHT));

    Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.7);
    {
        oscParamsComponent.setBounds(upperArea.removeFromLeft(280).reduced(PANEL_MARGIN));
        lfoParamsComponent.setBounds(upperArea.removeFromLeft(240).reduced(PANEL_MARGIN));
        ampEnvParamsComponent.setBounds(upperArea.removeFromLeft(240).reduced(PANEL_MARGIN));
        filterParamsComponent.setBounds(upperArea.reduced(PANEL_MARGIN));
    }

    Rectangle<int> lowerArea = bounds;
    {
        scopeComponent.setBounds(lowerArea.removeFromLeft(420).reduced(PANEL_MARGIN));
        driveParamsComponent.setBounds(lowerArea.removeFromLeft(100).reduced(PANEL_MARGIN));
        reverbParamsComponent.setBounds(lowerArea.removeFromLeft(280).reduced(PANEL_MARGIN));
        miscParamsComponent.setBounds(lowerArea.reduced(PANEL_MARGIN));
    }

}
