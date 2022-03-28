/*
  ==============================================================================

    AmpEnvelope.h
    Created: 23 Mar 2022 11:15:25pm
    Author:  tomo_

  ==============================================================================
*/

#pragma once

class AmpEnvelope
{
public:
    enum class AMPENV_STATE
    {
        ATTACK = 0,
        DECAY,
        SUSTAIN,
        RELEASE,
        WAIT,
    };

    AmpEnvelope(float attackTime, float decayTime, float sustain, float releaseTime);
    ~AmpEnvelope();

    AMPENV_STATE getState();
    float getValue();
    void setParameters(float attackTime, float decayTime, float sustain, float releaseTime);
    void attackStart();
    void releaseStart();
    void releaseEnd();
    bool isHolding();
    bool isReleasing();
    void cycle(float sampleRate);

private:
    AmpEnvelope();

    AMPENV_STATE _ampState;
    float _attackTime, _decayTime, _sustainValue, _releaseTime;
    float _value, _valueOnReleaseStart;
    float _sampleRate;
};
