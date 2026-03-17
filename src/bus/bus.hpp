#pragma once

#include <array>
#include <cstdint>
#include "abstract_bus.hpp"

namespace PPU {
  class PPU;
}

namespace Bus {
  class Bus final : public AbstractBus {
  public:
    Bus() = delete;

    Bus(std::array<std::uint8_t, 0x10000> &data, PPU::PPU &ppu);

  	// Asserts due to R/W permissions
  	// https://www.nesdev.org/wiki/PPU_registers#Summary

    std::uint8_t cpu_read(std::uint16_t address) override;
    void cpu_write(std::uint16_t address, std::uint8_t data) override;

    std::uint8_t &ppu_get_register(std::uint16_t address);

  private:
    static bool in_range(std::uint16_t address,
                         std::uint16_t start,
                         std::uint16_t end);

    PPU::PPU &ppu;

    std::array<std::uint8_t, 0x800> ram{};
    std::array<std::uint8_t, 0x8000> rom{};
  };
}
