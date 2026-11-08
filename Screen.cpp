#include <iostresm>
#include "Screen.h"

using namespace std;

void Screen::write(uint8_t data){
    buffer_.push_back(data);
}

void Screen::clear(){
    buffer_.clear();
}

void Screen::render(){
    cout << buffer_ ;
}