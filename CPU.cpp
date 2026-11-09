#include <iostream>
#include "Registers2.h"
#include "Instructions2.h"
#include "Memory.h"
#include "ALU.h"
#include "CPU2.h" 

using namespace std;

CPU::CPU(Memory& mem) : memory(mem) {
    pc = 0;
    running = true;
}

bool CPU::isHalted() const {
    return !running;
}

int CPU::fetch(int address) { 
    
    int highByte = memory.read(address);
    int lowByte = memory.read(address + 1);
    return (highByte << 8) | lowByte;
}

void CPU::execute(int opcode) {
    
    int op = (opcode >> 12) & 0xF;
    

    rawinst = instruction(opcode);

    switch (op) {
        case 1: {
           int reg1 = rawinst.getr();
           int location = rawinst.getaddress();
           int valuel = memory.read(location);
           order.set(reg1, valuel);
           break;
        }
        case 2: {
           int reg2 = rawinst.getr();
           int value2 = rawinst.getvalue();
           order.set(reg2, value2);
           break;
        }
        case 3: {
           int reg3 = rawinst.getr();
           int location3 = rawinst.getaddress();
           int value3 = order.get(reg3);
           memory.write(location3, value3);
           break;
        }
        case 4: {
           int reg4 = rawinst.getr();
           int temp = order.get(reg4);
           int regs = rawinst.getvalue();
           order.set(regs, temp);
           break;
        }
        case 5: {
           int reg5 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result1 = alu.addTwoComplement(order.get(rega), order.get(regb));
           order.set(reg5, result1);
           break;
        }
        case 6: {
           int reg6 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result2 = alu.addFloatingPoint(order.get(rega), order.get(regb));
           order.set(reg6, result2);
           break;
        }
        case 7: {
           int reg7 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result3 = alu.bitwiseOr(order.get(rega), order.get(regb)); 
           order.set(reg7, result3);
           break;
        }
        case 8: {
           int reg8 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result4 = alu.bitwiseAnd(order.get(rega), order.get(regb));
           order.set(reg8, result4);
           break;
        }
        case 9: {
           int reg9 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result5 = alu.bitwiseXor(order.get(rega), order.get(regb));
           order.set(reg9, result5);
           break;
        }
        case 0xA: 
        {
           int reg10 = rawinst.getr();
           int steps = rawinst.getvalue();
           int currentvalue = order.get(reg10);
           int result6 = alu.rotateRight(currentvalue, steps);
           order.set(reg10, result6);
           break;
        }
        case 0xB: 
        {
           int reg11 = rawinst.getr();
           int locationb = rawinst.getAddressOrValue();
           if(order.get(reg11) == order.get(0)){
               pc = locationb;
           }
           break;
        }
        case 0xC: 
        {
           running = false;
           break;
        }
        default:
           break;
    }
}

void CPU::step() {
    int currentpc = pc;
    int instructioncode = fetch(currentpc);
    execute(instructioncode);
    if (pc == currentpc) {
        pc += 2; 
    }
}

void CPU::run() {
    while (running) {
        step();
    }
}

void CPU::reset() {
    pc = 0;
    running = true;
    order = registerfile();
}
