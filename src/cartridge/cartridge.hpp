//
// Created by remza on 13.05.2025.
//

#pragma once

#include <cstdint>
#include <vector>

namespace Cartridge {
class Cartridge {
public:
  virtual ~Cartridge() = default;

  virtual std::uint16_t map_cpu_read(std::uint16_t address) = 0;
  virtual bool map_cpu_write(std::uint16_t address, std::uint8_t data) = 0;
};
} // namespace Cartridge

