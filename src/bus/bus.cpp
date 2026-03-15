#include "bus.hpp"
#include "../ppu/ppu.hpp"

#include <algorithm>
#include <stdexcept>

namespace Bus {
    Bus::Bus(std::array<std::uint8_t, 0x10000> &data, PPU::PPU &ppu)
        : ppu(ppu) {
        std::copy(data.begin(), data.begin() + 0x0800, ram.begin());
        std::copy(data.begin() + 0x8000, data.begin() + 0x10000, rom.begin());
    }

    std::uint8_t Bus::cpu_read(const std::uint16_t address) {
        if (in_range(address, 0x0000, 0x1FFF)) {
            if (address == PPU::Registers::STATUS)
                ppu.latch_reset();

            return ram[address % 0x0800];
        }

        if (in_range(address, 0x8000, 0xFFFF))
            return rom[address - 0x8000];

        return 0xFF;
    }

    void Bus::cpu_write(const std::uint16_t address, const std::uint8_t data) {
        if (address >= 0x2000) {
            ram[address % 0x0800] = data;

            if (address == PPU::Registers::SCROLL ||
                address == PPU::Registers::VRAM_ADDRESS)
                ppu.latch_set();

        }
    }

    std::uint8_t &Bus::ppu_get_register(const std::uint16_t address) {
        if (in_range(address, 0x2000, 0x2007))
            return ram[address % 8];

        throw std::out_of_range("PPU register address out of range");
    }

    bool Bus::in_range(const std::uint16_t address,
                       const std::uint16_t start,
                       const std::uint16_t end) {
        return address >= start && address <= end;
    }
}
