/*
  ==============================================================================

    TinySynthSound.cpp
    Created: 23 Mar 2022 11:16:21pm
    Author:  tomo_

  ==============================================================================
*/

#include "TinySynthSound.h"

TinySynthSound::TinySynthSound(const BigInteger& notes, const BigInteger& channels)
    : midiNotes(notes), midiChannels(channels)
{
}

// デストラクタ
TinySynthSound::~TinySynthSound()
{
}

bool TinySynthSound::appliesToNote(int midiNoteNumber)
{
    DBG("[appliesToNote] " + String("MidiNoteNumber: ") + String(midiNoteNumber));

    return midiNotes[midiNoteNumber];
}

bool TinySynthSound::appliesToChannel(int midiChannel)
{
    DBG("[appliesToChannel] " + String("MidiChannel: ") + String(midiChannel));

    return midiChannels[midiChannel];
}
