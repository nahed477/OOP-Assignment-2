#pragma once
#include <cstdint>
#include <string>
#include "IOutputDevice.h"

using namespace std;

class Screen : public IOutputDevice{
    private:
    string buffer_;
    public:
    Screen() = default;

    void write(uint8_t data);
    void clear();
    void render();
};