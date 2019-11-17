#pragma once

#include <memory>

class MidiGenerator
{
public:
    MidiGenerator();
    virtual ~MidiGenerator();

    virtual bool noteOn(const unsigned char& note);
    virtual bool noteOff(const unsigned char& note);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};