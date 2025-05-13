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

class AbstractBus {
public:
  virtual ~AbstractBus() = default;
  AbstractBus() = default;

  virtual std::uint8_t cpu_read(std::uint16_t address) = 0;
  virtual void cpu_write(std::uint16_t address, std::uint8_t data) = 0;
};

class FakeBus final : public AbstractBus {
public:
  explicit FakeBus(std::array<std::uint8_t, 0xFFFF + 1> &data) {
    std::copy(data.begin(), data.end(), memory.begin());
  }

  std::uint8_t cpu_read(const std::uint16_t address) override {
    return memory[address];
  }
  void cpu_write(const std::uint16_t address,
                 const std::uint8_t data) override {
    memory[address] = data;
  }

private:
  std::array<std::uint8_t, 0xFFFF> memory{};
};

class Bus final : public AbstractBus {
public:
  Bus() = default;

  explicit Bus(std::array<std::uint8_t, 0xFFFF> &data) {
    std::copy(data.begin() + 0x0000, data.begin() + 0x0800, ram.begin());
    std::copy(data.begin() + 0x8000, data.begin() + 0xFFFF, rom.begin());
  }

  std::uint8_t cpu_read(const std::uint16_t address) override {

    if (address < 0x2000) {
      return ram[address % 0x0800];
    }

    if (address >= 0x8000) {
      return rom[address - 0x8000];
    }

    return 0xFF;
  }

  void cpu_write(const std::uint16_t address,
                 const std::uint8_t data) override {
    if (address >= 0x2000) {
      ram[address % 0x0800] = data;
    }
  }

private:
  std::array<std::uint8_t, 0x800> ram{};
  std::array<std::uint8_t, 0x8000> rom{};
};
} // namespace Bus

#endif // BUS_HPP
