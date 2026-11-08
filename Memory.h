#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include "IOutputDevice.h"

using namespace std;

class Memory{
    private:
    array<uint8_t, 256> cells_;
    IOutputDevice* outputDevice_;
    public:
    Memory();

    uint8_t read(uint8_t address) const;
    void write(uint8_t address, uint8_t value);
    bool loadProgram(const vector<uint8_t>& program, uint8_t startAddress);
    void reset();
    void attachOutputDevice(IOutputDevice& device);
};