#include "Registers.h"

registerfile ::registerfile(){
    for(int i=0;i<16; i++){
        registers[i]=0;
    }
}

int registerfile :: get(int index){
    return registers[index];
}

void registerfile:: set(int index, int value){
    registers[index] = value;
}
