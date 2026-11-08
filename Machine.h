#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include "CPU.h"
#include "Memory.h"
#include "Screen.h"

class Machine {
private:
    Memory memory;
    Screen screen;
    CPU cpu;

public:
    Machine();

    bool loadProgram(const std::string& filePath, uint8_t startAddress);
    void run();
    void step();
    void reset();

    CPU& getCPU();
    Memory& getMemory();
    Screen& getScreen();

    void startUI();
};
#endif
