#include <iostream>
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

using namespace std;
class instruction {
private:
int raw;
int oper;
int r;
int address;
int value;
public:
instruction(){
  raw=0;
  oper=0;
  r=0;
  address=0;
  value=0;

}
void cutting (int raw){
    oper = raw/ (16*16*16);
    raw=raw%(16*16*16);

    r = raw / (16*16);
    raw=raw % (16*16);

    address=raw/16;
    raw=raw % 16;
    value=raw;
}
instruction(int requestedinstruction){
    cutting(requestedinstruction);
}
int getoper(){
    return oper;
}
int getr(){
 return r;
}
int getaddress(){
    return address;
}
int getvalue(){
    return value;
}


};

#endif

