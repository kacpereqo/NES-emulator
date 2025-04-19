//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef NES_H
#define NES_H

#include "../apu/apu.h"
#include "../cpu/cpu.h"
#include "../ppu/ppu.h"

namespace NES {
    class NES {
    private:
        CPU::CPU cpu;
        APU::APU apu;
        PPU::PPU ppu;

        std::array<std::uint8_t, 0xFFFF> memory{};

    public:
        void run(){}
        NES() : cpu{memory} {}
    };
}

#endif //NES_H
