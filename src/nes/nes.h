//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef NES_H
#define NES_H

#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../apu/apu.h"
#include "../bus/bus.hpp"
#include "../cpu/cpu.h"
#include "../ppu/ppu.h"

/// https://www.nesdev.org/wiki/CPU_memory_map
// Address range 	Size 	Device
// $0000–$07FF   	$0800 	2 KB internal RAM

// $0800–$0FFF 	    $0800 	Mirrors of $0000–$07FF
// $1000–$17FF 	    $0800
// $1800–$1FFF 	    $0800

// $2000–$2007 	    $0008 	NES PPU registers
// $2008–$3FFF 	    $1FF8 	Mirrors of $2000–$2007 (repeats every 8 bytes)
// $4000–$4017 	    $0018 	NES APU and I/O registers
// $4018–$401F 	    $0008 	APU and I/O functionality that is normally
// disabled. See CPU Test Mode. $4020–$FFFF      $BFE0   PRG ROM, PRG RAM, or
// other memory
// - $6000–$7FFF    $2000   Usually cartridge RAM, when present.
// - $8000–$FFFF 	$8000   Usually cartridge ROM and mapper registers.

// struct Memory {
//     std::array<std::uint8_t, 0x8000> internal_ram{};
//     std::array<std::uint8_t, 0x8000> mirror_ram_1{};
//     std::array<std::uint8_t, 0x8000> mirror_ram_2{};
//     std::array<std::uint8_t, 0x8000> mirror_ram_3{};
//     std::array<std::uint8_t, 0x0008> ppu_registers{};
//     std::array<std::uint8_t, 0x1FF8> mirror_ppu_registers{};
//     std::array<std::uint8_t, 0x0018> apu_io_registers{};
//     std::array<std::uint8_t, 0x0008> apu_io_disabled{};
//     std::array<std::uint8_t, 0xBFE0> other_memory{};
//     std::array<std::uint8_t, 0x2000> cartridge_ram{};
//     std::array<std::uint8_t, 0x8000 - 0x06> cartridge_rom{};
//     std::array<std::uint8_t, 0x06> reset_vector_table{};
// };

namespace NES {
class NES {

public:
  [[noreturn]] void run() {
    for (int i = 0; i < 10; i++) {
      cpu.run();

      for (int j = 0; j < 3; j++)
        ppu.run();
    }
  }
  NES() : cpu{bus}, apu{memory}, ppu(memory) {
    cpu.init();
    apu.init();
    ppu.init();
  }

private:
  CPU::CPU cpu;
  APU::APU apu;
  PPU::PPU ppu;

  Bus::Bus bus;

  std::array<std::uint8_t, 0xFFFF> memory{};
};
} // namespace NES

#endif // NES_H
