//
// Created by remza on 13.05.2025.
//

#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <cstdint>
#include <vector>

namespace Cartridge {
class Cartridge {
public:
  virtual ~Cartridge() = default;

  // Translate CPU address to PRG ROM address
  virtual std::uint16_t map_cpu_read(std::uint16_t address) = 0;
  virtual bool map_cpu_write(std::uint16_t address, std::uint8_t data) = 0;
};
} // namespace Cartridge

#endif // CARTRIDGE_HPP
