#include "Memory.h"

using namespace std;

Memory::Memory() : outputDevice_(nullptr) {
    reset();
}
uint8_t Memory::read(uint8_t address) const{
    return cells_[address];
}
void Memory::write(uint8_t address, uint8_t value) {
    cells_[address] = value;
    
    if (address == 0xFF && outputDevice_ != nullptr) {
        outputDevice_->write(value);
    }
}
bool Memory::loadProgram(const vector<uint8_t>& program, uint8_t startAddress) {
    uint16_t currentAddress = startAddress;
    for (uint8_t byte : program) {
        if (currentAddress >= 256) {
            return false;
        }
        cells_[currentAddress++] = byte;
    }
    return true;
}
void Memory::reset() {
    cells_.fill(0);
}
void Memory::attachOutputDevice(IOutputDevice& device) {
    outputDevice_ = &device;
}