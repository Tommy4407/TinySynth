/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DSP/TinySynthParameters.h"

#include "GUI/ScopeComponent.h"

//==============================================================================
/**
*/
class TinySynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TinySynthAudioProcessor();
    ~TinySynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    void changeVoiceSize();

    MidiKeyboardState& getKeyboardState() { return keyboardState; }

    AudioBufferQueue<float>& getAudioBufferQueue() { return scopeDataQueue; }

    const StringArray LFO_TARGETS{ "None", "WaveLevel", "WaveAngle" };
    const StringArray LFO_WAVE_TYPES{ "Sine", "Saw", "Tri", "Square", "Noise" };
    const StringArray FILTER_TYPES{ "Low-Pass", "High-Pass", "Band-Pass" };

    OscillatorParameters oscParameters;
    LfoParameters lfoParameters;
    AmpEnvelopeParameters ampEnvParameters;
    FilterParameters filterParameters;
    ReverbParameters reverbParameters;
    AudioParameterFloat* driveParameter;
    AudioParameterFloat* masterVolumePrameter;
    AudioParameterInt* voiceSizeParameter;
    AudioParameterBool* velocitySenseParameter;

private:
    Synthesiser   synth;

    dsp::ProcessSpec spec;

    dsp::WaveShaper<float> clipper, limiter;

    static float clippingFunction(float inputValue);

    dsp::Gain<float> drive, masterVolume;                   // 波形の振幅を増減するDSPオブジェクトの宣言

    dsp::Reverb reverb;

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> iirFilter;

    MidiKeyboardState keyboardState;

    AudioBufferQueue<float> scopeDataQueue;
    ScopeDataCollector<float> scopeDataCollector;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TinySynthAudioProcessor)
};
