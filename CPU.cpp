#include <iostream>
#include "Registers.h"
#include "Instruction.h"
#include "Memory.h"
#include "ALU.h"
#include "CPU.h"

using namespace std;

CPU :: CPU(){
    pc=0;
    running=true;
}
CPU::CPU(int rawin): rawinst (rawin){
    pc=0;
    running = true;
}
int CPU::fetch(int address){ 
    int instructionvalue = memory.read(address);
    return instructionvalue;
}
void CPU::execute(int opecode){
    int op=opecode;
    switch (op) {
        case 1: 
       int reg1=rawinst.getr();
       int location = rawinst.getaddress();
       int valuel= memory.read(location);
       order.set(reg1,valuel);

        break;
        case 2:
         int reg2=rawinst.getr();
         int value2=rawinst.getvalue();
         order.set(reg2,value2);
        break;
        case 3:
        int reg3=rawinst.getr();
        int location3 = rawinst.getaddress();
        int value3 =order.get(reg3);
        memory.write(location3,value3);
        
        break;
        case 4:
        int reg4=rawinst.getr();
        int temp=order.get(reg4);
        int regs=rawinst.getvalue();
        order.set(regs,temp);
        break;
        case 5:
        int reg5=rawinst.getr();
        int rega=rawinst.getaddress();
        int regb=rawinst.getvalue();

        int result1=alu.addTwoComplement(order.get(rega),order.get(regb));
        order.set(reg5,result1);

        break;
        case 6:
        int reg6=rawinst.getr();
        int rega=rawinst.getaddress();
        int regb=rawinst.getvalue();
        int result2=alu.addFloatingPoint(order.get(rega),order.get(regb));
    
        order.set(reg6,result2);
        
        break;


         case 7: 
         int reg7=rawinst.getr();
         int rega=rawinst.getaddress();
         int regb=rawinst.getvalue();
         int result3=alu.bitwiseOr(order.get(rega), order.get(regb)); 
         order.set(reg7,result3);
        break;
        case 8:
        int reg8=rawinst.getr();
        int rega=rawinst.getaddress();
        int regb=rawinst.getvalue();
        int result4=alu.bitwiseAnd(order.get(rega), order.get(regb));
        order.set(reg8,result4);
        
        break;
        case 9:
        int reg9=rawinst.getr();
        int rega=rawinst.getaddress();
        int regb=rawinst.getvalue();
        int result5 = alu.bitwiseXor(order.get(rega),order.get(regb));
        order.set(reg9,result5);

        break;
        case 'A':
        case 'a':
        int reg10=rawinst.getr();
        int steps = rawinst.getvalue();
        int currentvalue = order.get(reg10);
        int result6 = alu.rotateRight(currentvalue, steps);
        order.set(reg10,result6);
        break;
        case 'B':
        case 'b':
        int reg11 = rawinst.getr();
        int locationb = (rawinst.getaddress() << 4) | rawinst.getvalue();
        if(order.get(reg11) == order.get(0)){
            pc = locationb;
        }
             

        break;
        case 'C':
        case 'c':
        running = false;
        break;

    }

}

void CPU::run(){
    while(running){
        int currentpc = pc;
        int instructioncode = fetch(currentpc);
        execute(instructioncode);
        if(pc == currentpc){
            pc += 2;
        }
    }
}

