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
           int location = (rawinst.getaddress() <<4) | rawinst.getvalue();
           int valuel = memory.read(location);
           order.set(reg1, valuel);
           cout << "[EXECUTE] R[" << reg1 << "] <- Memory[0x" << hex << location << dec << "] (" << valuel << ")\n";
           break;
        }
        case 2: {
           int reg2 = rawinst.getr();
           int value2 = (rawinst.getaddress() << 4) | rawinst.getvalue(); 
           order.set(reg2, value2);
           cout << "[EXECUTE] R[" << reg2 << "] <- Immediate Value (" << value2 << ")\n";
           break;
        }
       case 3: {
            int reg3 = rawinst.getr();
            int location3 = (rawinst.getaddress() << 4) | rawinst.getvalue();
            int value3 = order.get(reg3);
            memory.write(location3, value3);
            cout << "[EXECUTE] Memory[0x" << hex << location3 << dec << "] <- R[" << reg3 << "] (Value: 0x" << hex << uppercase << value3 << dec << nouppercase << ")\n";
            break;
        }
        case 4: {
           int reg4 = rawinst.getaddress();
           int temp = order.get(reg4);
           int regs = rawinst.getvalue();
           order.set(regs, temp);
           cout << "[EXECUTE] R[" << regs << "] <- R[" << reg4 << "] (" << temp << ")\n";
           break;
        }
        case 5: {
           int reg5 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result1 = (order.get(rega)+order.get(regb)) & 0xFF;
           order.set(reg5, result1);
           cout << "[EXECUTE] R[" << reg5 << "] <- R[" << rega << "] + R[" << regb << "] = " << result1 << "\n";
           break;
        }
        case 6: {
           int reg6 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result2 = alu.addFloatingPoint(order.get(rega), order.get(regb));
           order.set(reg6, result2);
           cout << "[EXECUTE] R[" << reg6 << "] <- R[" << rega << "] +F R[" << regb << "] = " << result2 << "\n";
           break;
        }
        case 7: {
           int reg7 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result3 = alu.bitwiseOr(order.get(rega), order.get(regb)); 
           order.set(reg7, result3);
           cout << "[EXECUTE] R[" << reg7 << "] <- R[" << rega << "] OR R[" << regb << "] = " << result3 << "\n";
           break;
        }
        case 8: {
           int reg8 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result4 = alu.bitwiseAnd(order.get(rega), order.get(regb));
           order.set(reg8, result4);
           cout << "[EXECUTE] R[" << reg8 << "] <- R[" << rega << "] AND R[" << regb << "] = " << result4 << "\n";
           break;
        }
        case 9: {
           int reg9 = rawinst.getr();
           int rega = rawinst.getaddress();
           int regb = rawinst.getvalue();
           int result5 = alu.bitwiseXor(order.get(rega), order.get(regb));
           order.set(reg9, result5);
           cout << "[EXECUTE] R[" << reg9 << "] <- R[" << rega << "] XOR R[" << regb << "] = " << result5 << "\n";
           break;
        }
        case 0xA: 
        {
           int reg10 = rawinst.getr();
           int steps = rawinst.getvalue();
           int currentvalue = order.get(reg10);
           int result6 = alu.rotateRight(currentvalue, steps);
           order.set(reg10, result6);
           cout << "[EXECUTE] R[" << reg10 << "] <- ROR(R[" << reg10 << "], " << steps << ") = " << result6 << "\n";
           break;
        }
      case 0xB: {
            int reg11 = rawinst.getr();
            
            int targetaddress = (rawinst.getaddress() << 4) | rawinst.getvalue();
            
            if (order.get(reg11) == order.get(0)) {
                pc = targetaddress;
            }
            cout << "[EXECUTE] Jump if R[" << reg11 << "] == R[0] to 0x" << hex << targetaddress << dec << "\n";
            break;
        }
        case 0xC: 
        {
           running = false;
           cout << "[EXECUTE] Program HALTED.\n";
           break;
        }
        default:
           break;
    }
}

void CPU::step() {
    int currentpc = pc;
    int instructioncode = fetch(currentpc);

    cout << "Current PC: 0x" << hex << currentpc << dec << "\n";
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
