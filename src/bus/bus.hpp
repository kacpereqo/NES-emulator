#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include "../cartridge/cartridge.hpp"
#include "abstract_bus.hpp"

namespace PPU {
  class PPU;
}

namespace Bus {
  class Bus final : public AbstractBus {
  public:

  	void insert_cartridge(std::vector<std::uint8_t> data);
  	void connect_ppu(PPU::PPU &ppu) { this->ppu = &ppu; }

  	// Asserts due to R/W permissions
  	// https://www.nesdev.org/wiki/PPU_registers#Summary

    std::uint8_t cpu_read(std::uint16_t address) override;
    void cpu_write(std::uint16_t address, std::uint8_t data) override;

    std::uint8_t &ppu_get_register(std::uint16_t address);

  private:
    static bool in_range(std::uint16_t address,
                         std::uint16_t start,
                         std::uint16_t end);

  	PPU::PPU * ppu = nullptr;

  	std::unique_ptr<Cartridge> cartridge;

    std::array<std::uint8_t, 0x800> ram{};
  };
}
