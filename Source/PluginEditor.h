/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "GUI/ParametersComponent.h"
#include "GUI/ScopeComponent.h"


//==============================================================================
/**
*/
class TinySynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TinySynthAudioProcessorEditor (TinySynthAudioProcessor&);
    ~TinySynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TinySynthAudioProcessor& audioProcessor;

    MidiKeyboardComponent keyboardComponent;
    ScopeComponent<float> scopeComponent;
    OscillatorParametersComponent oscParamsComponent;
    AmpEnvelopeParametersComponent ampEnvParamsComponent;
    LfoParametersComponent lfoParamsComponent;
    FilterParametersComponent filterParamsComponent;
    ReverbParametersComponent reverbParamsComponent;
    DriveParametersComponent driveParamsComponent;
    MiscParametersComponent miscParamsComponent;

    LookAndFeel* customLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TinySynthAudioProcessorEditor)
};
