#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <rtmidi/RtMidi.h>

#include "midi_generator.hpp"

/*
 * Channel voice message format:
 *
 * Voice Message           Status Byte      Data Byte1          Data Byte2
 * -------------           -----------   -----------------   -----------------
 * Note off                      8x      Key number          Note Off velocity
 * Note on                       9x      Key number          Note on velocity
 * Polyphonic Key Pressure       Ax      Key number          Amount of pressure
 * Control Change                Bx      Controller number   Controller value
 * Program Change                Cx      Program number      None
 * Channel Pressure              Dx      Pressure value      None            
 * Pitch Bend                    Ex      MSB                 LSB
 */

struct MidiGenerator::Impl
{
    std::shared_ptr<RtMidiOut> pMidiOut;
    std::vector<unsigned char> message;

    Impl() {
        // Reserve memory for 1 status and at most 2 data bytes
        message.reserve(3);

        // Create virutal MIDI output port
        pMidiOut = std::make_shared<RtMidiOut>();
        try {
            pMidiOut->openVirtualPort("CustomSynth Output");
        } catch (const std::exception& e) {
            std::cerr << "Failed to open virtual MIDI port: " << e.what() << std::endl;
        }
    }

    ~Impl() {
        
    }

    bool noteOn(const unsigned char& note) {
        message.clear();
        message.push_back(0x90);
        message.push_back(note);
        message.push_back(100);
        try {
            pMidiOut->sendMessage(&message);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to send note on MIDI message" << std::endl;
        }
        return false;
    }

    bool noteOff(const unsigned char& note) {
        message.clear();
        message.push_back(0x80);
        message.push_back(note);
        message.push_back(100);
        try {
            pMidiOut->sendMessage(&message);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to send note off MIDI message" << std::endl;
        }
        return false;
    }
};

MidiGenerator::MidiGenerator()
    : pImpl(new Impl()) {
}

MidiGenerator::~MidiGenerator() {
}

bool MidiGenerator::noteOn(const unsigned char& note) {
    return pImpl->noteOn(note);
}

bool MidiGenerator::noteOff(const unsigned char& note) {
    return pImpl->noteOff(note);
}