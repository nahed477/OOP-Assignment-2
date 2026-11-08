#ifndef CPU_H
#define CPU_H
#include "Registers.h"
#include "Instruction.h"
#include "Memory.h"
#include "ALU.h"

class CPU{
private:
instruction rawinst;
registerfile order;
Memory memory;
ALU alu;
int operand;
int pc;
bool running;
public:
CPU();
CPU(int rawin);
int fetch(int address);
void execute(int opecode);
void run();
};
#endif
