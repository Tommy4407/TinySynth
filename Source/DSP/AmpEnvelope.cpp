/*
  ==============================================================================

    AmpEnvelope.cpp
    Created: 23 Mar 2022 11:15:25pm
    Author:  tomo_

  ==============================================================================
*/

#include "AmpEnvelope.h"

namespace
{
    const float AMP_MAX = 1.0f;
    const float AMP_MIN = 0.0f;
    const float ATTACK_MIN = 0.01f;
    const float DECAY_MIN = 0.01f;
    const float RELEASE_MIN = 0.01f;
}

AmpEnvelope::AmpEnvelope(float attackTime, float decayTime, float sustain, float releaseTime)
    : _attackTime(attackTime), _decayTime(decayTime), _sustainValue(sustain), _releaseTime(releaseTime)
    , _sampleRate(0.0f), _value(0.0f), _valueOnReleaseStart(0.0f), _ampState(AMPENV_STATE::WAIT)
{
    if (_attackTime <= ATTACK_MIN) {
        _attackTime = ATTACK_MIN;
    }

    if (_decayTime <= DECAY_MIN) {
        _decayTime = DECAY_MIN;
    }

    if (_releaseTime <= RELEASE_MIN) {
        _releaseTime = RELEASE_MIN;
    }

    if (_sustainValue > AMP_MAX) {
        _sustainValue = AMP_MAX;
    }

    if (_sustainValue < AMP_MIN) {
        _sustainValue = AMP_MIN;
    }
}

AmpEnvelope::~AmpEnvelope()
{}

AmpEnvelope::AMPENV_STATE  AmpEnvelope::getState()
{
    return _ampState;
}

float AmpEnvelope::getValue()
{
    return _value;
}

void AmpEnvelope::setParameters(float attackTime, float decayTime, float sustain, float releaseTime)
{
    _attackTime = attackTime;
    _decayTime = decayTime;
    _sustainValue = sustain;
    _releaseTime = releaseTime;

    if (_attackTime <= ATTACK_MIN) {
        _attackTime = ATTACK_MIN;
    }

    if (_decayTime <= DECAY_MIN) {
        _decayTime = DECAY_MIN;
    }

    if (_releaseTime <= RELEASE_MIN) {
        _releaseTime = RELEASE_MIN;
    }

    if (_sustainValue > AMP_MAX) {
        _sustainValue = AMP_MAX;
    }

    if (_sustainValue < AMP_MIN) {
        _sustainValue = AMP_MIN;
    }
}

void AmpEnvelope::attackStart()
{
    if (!isReleasing())
    {
        _value = AMP_MIN;
    }
    _ampState = AMPENV_STATE::ATTACK;
}

void AmpEnvelope::releaseStart()
{
    if (isHolding())
    {
        _ampState = AMPENV_STATE::RELEASE;
        _valueOnReleaseStart = _value;
    }
}

void AmpEnvelope::releaseEnd()
{
    _value = AMP_MIN;
    _ampState = AMPENV_STATE::WAIT;
}

bool AmpEnvelope::isHolding()
{
    if (_ampState == AmpEnvelope::AMPENV_STATE::ATTACK
        || _ampState == AmpEnvelope::AMPENV_STATE::DECAY
        || _ampState == AmpEnvelope::AMPENV_STATE::SUSTAIN)
    {
        return true;
    }
    return false;
}

bool AmpEnvelope::isReleasing()
{
    return _ampState == AmpEnvelope::AMPENV_STATE::RELEASE;
}

void AmpEnvelope::cycle(float sampleRate)
{
    _sampleRate = sampleRate;
    switch (_ampState)
    {
    case AMPENV_STATE::ATTACK:
        _value += AMP_MAX / (_sampleRate * _attackTime);
        if (_value >= AMP_MAX)
        {
            _value = AMP_MAX;
            _ampState = AMPENV_STATE::DECAY;
        }
        break;

    case AMPENV_STATE::DECAY:
        _value -= AMP_MAX / (_sampleRate * _decayTime);
        if (_value <= _sustainValue)
        {
            _value = _sustainValue;
            _ampState = AMPENV_STATE::SUSTAIN;
        }
        break;

    case AMPENV_STATE::SUSTAIN:
        _value = _sustainValue;
        break;

    case AMPENV_STATE::RELEASE:
        _value -= _valueOnReleaseStart / (_sampleRate * _releaseTime);
        if (_value <= AMP_MIN)
        {
            _value = AMP_MIN;
            _ampState = AMPENV_STATE::WAIT;
        }
        break;

    case AMPENV_STATE::WAIT:
        _value = AMP_MIN;
        break;
    }
}
