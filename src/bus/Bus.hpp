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
  std::array<std::byte, 0xFFFF> memory{};

  std::byte read(const std::uint16_t address) const {
    return this->memory[address];
  }

  void write(const std::uint16_t address, const std::byte value) {
    this->memory[address] = value;
  }
};
} // namespace Bus

#endif // BUS_HPP
