//
// Created by remza on 04.05.2025.
//

#ifndef BUS_HPP
#define BUS_HPP
#include "../apu/apu.h"
#include "../cpu/cpu.h"
#include "../ppu/ppu.h"

namespace Bus {
class Bus {
public:
  Bus(APU::APU &apu, CPU::CPU &cpu, PPU::PPU &ppu)
      : apu{apu}, cpu{cpu}, ppu{ppu} {}

private:
  APU::APU &apu;
  CPU::CPU &cpu;
  PPU::PPU &ppu;
};
} // namespace Bus

#endif // BUS_HPP
