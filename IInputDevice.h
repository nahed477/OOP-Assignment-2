#pragma once
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class IInputDevice{
    public:
    virtual uint8_t read() = 0;
    virtual bool hasinput() const = 0;
    virtual ~IInputDevice () {};
};