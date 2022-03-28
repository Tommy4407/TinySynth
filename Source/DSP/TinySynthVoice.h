/*
  ==============================================================================

    TinySynthVoice.h
    Created: 23 Mar 2022 11:16:54pm
    Author:  tomo_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TinySynthParameters.h"
#include "Waveforms.h"
#include "AmpEnvelope.h"
#include "TinySynthSound.h"

class TinySynthVoice : public SynthesiserVoice
{
public:
    TinySynthVoice(OscillatorParameters* oscParams, LfoParameters* lfoParams, AmpEnvelopeParameters* ampEnvParams, AudioParameterBool* velocitySenseParam);

    virtual ~TinySynthVoice();

    virtual bool canPlaySound(SynthesiserSound* sound) override;
    virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    virtual void stopNote(float velocity, bool allowTailOff) override;
    virtual void pitchWheelMoved(int newPitchWheelValue) override;
    virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
    virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    float calcModulationFactor(float angle);

    float currentAngle, lfoAngle, angleDelta;
    float level, lastLevel, levelDiff;
    float pitchBend;

    Waveforms waveForms;
    AmpEnvelope ampEnv;

    OscillatorParameters* _oscParamsPtr;
    LfoParameters* _lfoParamsPtr;
    AmpEnvelopeParameters* _ampEnvParamsPtr;
    AudioParameterBool* _velocitySenseParamPtr;
};
