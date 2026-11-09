#include <iostream>
#include <iomanip>
#include "Screen.h"

using namespace std;

void Screen::write(uint8_t data){
    buffer_.push_back(data);
}

void Screen::clear(){
    buffer_.clear();
}

void Screen::render() {
    for (uint8_t ch : buffer_) {
        cout << hex << uppercase << setfill('0') << setw(2) << static_cast<int>(ch) << " ";
    }
    cout << dec;  
}