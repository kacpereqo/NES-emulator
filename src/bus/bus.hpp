//
// Created by remza on 04.05.2025.
//

#ifndef BUS_HPP
#define BUS_HPP
#include "../apu/apu.h"
#include "../cpu/cpu.h"
#include "../ppu/ppu.h"

namespace Bus {

constexpr std::uint16_t RAM_SIZE = 0x0800; // 2KB of RAM

class Bus {
public:
    std::byte read(const std::uint16_t address) const {
        return ram[address % RAM_SIZE];
    }

    void write(const std::uint16_t address,const std::byte value) {
        ram[address % RAM_SIZE] = value;
    }

private:
    std::array<std::byte, RAM_SIZE> ram{};
};
} // namespace Bus

#endif // BUS_HPP
