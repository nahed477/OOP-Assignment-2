#ifndef CPU_H
#define CPU_H
#include "Registers2.h"
#include "Instructions2.h"
#include "Memory.h"
#include "ALU.h"

class CPU {
private:
    instruction rawinst;
    registerfile order;
    Memory& memory; 
    ALU alu;
    int pc;
    bool running;

public:
    CPU(Memory& mem); 
    bool isHalted() const;
    void step();
    void reset();
    int fetch(int address);
    void execute(int opcode);
    void run();
};
#endif
