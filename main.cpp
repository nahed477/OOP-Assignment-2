#include <iostream>
#include "Machine.h"
using namespace std;

int main() {
    Machine machine;
    string filename;
    cout << "Enter the program file name";
    cin >> filename;
    machine.loadProgram(filename);
    machine.execute();
    return 0;
}
