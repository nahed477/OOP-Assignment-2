#pragma once
#include <cstdint>

using namespace std;

class IOutputDevice{
    public:
    virtual void write(uint8_t value) = 0;
    virtual void clear() = 0;
    virtual ~IOutputDevice () {};
};