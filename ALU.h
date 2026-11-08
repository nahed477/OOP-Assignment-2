#include<cstdint>
class ALU
{
public:

    uint8_t addTwoComplement(uint8_t a, uint8_t b)
    {
        return a + b;
    } 

    uint8_t addFloatingPoint(uint8_t a, uint8_t b)
    {
        return a + b;
    }

     uint8_t bitwiseOr(uint8_t a, uint8_t b)
    {
        return a | b;
    }

    uint8_t bitwiseAnd(uint8_t a, uint8_t b) 
    {
        return a & b;
    }

    uint8_t bitwiseXor(uint8_t a, uint8_t b) 
    {
        return a ^ b;
    }

    uint8_t rotateRight(uint8_t val, uint8_t steps) 
    {
        steps % = 8;
        return (val >> steps) | (val << (8 - steps));
    }
};
