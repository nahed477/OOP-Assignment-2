#ifndef REGISTERS_H
#define REGISTERS_H

#include<iostream>

using namespace std;

class registerfile {
private:
int registers[16];
public:
registerfile(){
    for(int i=0;i<16; i++){
        registers[i]=0;
    }
}
int get(int index){
 return registers[index];
}
void set(int index, int value){
    registers[index]=value;
}
};
#endif
