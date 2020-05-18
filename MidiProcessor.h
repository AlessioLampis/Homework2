/*
  ==============================================================================

    MidiProcessor.h
    Created: 17 May 2020 11:46:22pm
    Author:  Alessio

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MidiProcessor
{
    public:
        void process(MidiBuffer& midiMessages)
    {
        MidiBuffer::Iterator it(midiMessages);
        MidiMessage currentMessage;
        int samplePos;
        
        while (it.getNextEvent(currentMessage, samplePos))
        {
            DBG(currentMessage.getDescription());
            
        }
    }
};
