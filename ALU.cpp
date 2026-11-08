#include "ALU.h"

uint8_t ALU::addTwoComplement(uint8_t a, uint8_t b)
{
    return a + b;
} 
uint8_t ALU::addFloatingPoint(uint8_t a, uint8_t b)
{
    return a + b;
}
uint8_t ALU::bitwiseOr(uint8_t a, uint8_t b)
{
    return a | b;
}
uint8_t ALU::bitwiseAnd(uint8_t a, uint8_t b) 
{
    return a & b;
}
uint8_t ALU::bitwiseXor(uint8_t a, uint8_t b) 
{
    return a ^ b;
}
uint8_t ALU::rotateRight(uint8_t val, uint8_t steps) 
{
    steps %=8;
    return (val >> steps) | (val << (8 - steps));
}

