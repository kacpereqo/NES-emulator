#include <iostream>
#include "src/nes/nes.h"
#include "src/apu/apu.h"
#include <SDL2/SDL.h>

int main(int argv, char** args) {
    std::array<std::uint8_t, 0xFFFF> memory{};
    APU::APU apu{memory};

    return 0;
}
