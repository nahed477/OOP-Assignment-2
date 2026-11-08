#include <cstdint>
#ifndef ALU_H
#define ALU_H
class ALU
{
public:
    uint8_t addTwocomplement(uint8_t a, uint8_t b);
    uint8_t addFloatingPoint(uint8_t a, uint8_t b);
    uint8_t bitwiseOr(uint8_t a, uint8_t b);
    uint8_t bitwiseAnd(uint8_t a, uint8_t b);
    uint8_t bitwiseXor(uint8_t a, uint8_t b);
    uint8_t rotateRight(uint8_t val, uint8_t steps);
};
#endif
