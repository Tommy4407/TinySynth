/*
  ==============================================================================

    TinySynthSound.h
    Created: 23 Mar 2022 11:16:21pm
    Author:  tomo_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TinySynthSound : public SynthesiserSound
{
public:
    TinySynthSound(const BigInteger& notes, const BigInteger& channels);

    virtual ~TinySynthSound();

    virtual bool appliesToNote(int midiNoteNumber) override;
    virtual bool appliesToChannel(int midiChannel) override;

private:
    BigInteger midiNotes;
    BigInteger midiChannels;

};
