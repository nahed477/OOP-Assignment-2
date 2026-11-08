#ifndef REGISTERS_H
#define REGISTERS_H
#include <iostream>

using namespace std;
class registerfile{
private:
int registers[16];
public:

registerfile();
int get(int index);
void set(int index, int value );


};
#endif 
