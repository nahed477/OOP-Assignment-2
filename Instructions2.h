#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>

using namespace std;

class instruction{
private:
int raw;
int oper;
int r;
int address;
int value;

public:
instruction();
instruction(int requestedinstruction);
void cutting(int raw);
int getoper();
int getr();
int getaddress();
int getvalue();

};

#endif


