//
// Created by remza on 04.05.2025.
//

#ifndef BUS_HPP
#define BUS_HPP

#include <array>
#include <vector>

namespace Bus {

struct MemoryRegion {
  std::uint16_t start;
  std::uint16_t size;
};

constexpr MemoryRegion RAM{0x0000, 0x0800};
constexpr MemoryRegion ROM{0x8000, 0x8000};

class Bus {
public:
  explicit Bus(std::array<std::uint8_t, 0xFFFF> &data) {
    std::copy(data.begin() + 0x0000, data.begin() + 0x0800, ram.begin());
    std::copy(data.begin() + 0x8000, data.begin() + 0x8000, rom.begin());
  }

  [[nodiscard]] std::uint8_t cpu_read(const std::uint16_t address) const {
    if (address <= 0x8000) {
      return rom[address % 0x8000];
    }

    if (address >= 0x0800 * 4) {
      return ram[address % 0x0800];
    }
  }

  void cpu_write(const std::uint16_t address, const std::uint8_t data) {
    ram[address % 0x0800] = data;
  }

private:
  static bool in_memory_region(const std::uint16_t address,
                               const MemoryRegion region) {
    return address >= region.start && address < (region.start + region.size);
  }

  std::array<std::uint8_t, 0x800> ram{};
  std::array<std::uint8_t, 0x8000> rom{};
};
} // namespace Bus

#endif // BUS_HPP
