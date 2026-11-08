#include "Instruction.h"

instruction::instruction(){
raw =0;
oper=0;
r=0;
address=0;
value=0;
}

void instruction :: cutting(int raw){
    oper = raw/ (16*16*16);
    raw=raw%(16*16*16);

    r = raw / (16*16);
    raw=raw % (16*16);

    address=raw/16;
    raw=raw % 16;
    value=raw;
    
}
instruction :: instruction(int requestedinstruction){
    cutting(requestedinstruction);
}
int instruction::getoper(){
    return oper;
}
int instruction::getr(){
    return r;
}
int instruction::getaddress(){
    return address;
}
int instruction::getvalue(){
    return value;
}
