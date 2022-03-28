/*
  ==============================================================================

    Waveforms.h
    Created: 23 Mar 2022 11:17:04pm
    Author:  tomo_

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Waveforms
{
public:
    float sine(float angle);
    float saw(float angle);
    float square(float angle);
    float triangle(float angle);
    float noise();

private:
    Random whiteNoise;
};
