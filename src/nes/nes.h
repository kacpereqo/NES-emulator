//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef NES_H
#define NES_H

#include <array>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

#include "../apu/apu.h"
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
// $4018–$401F 	    $0008 	APU and I/O functionality that is normally disabled. See CPU Test Mode.
// $4020–$FFFF      $BFE0   PRG ROM, PRG RAM, or other memory
// - $6000–$7FFF    $2000   Usually cartridge RAM, when present.
// - $8000–$FFFF 	$8000   Usually cartridge ROM and mapper registers.

// struct Memory {
//
//     std::array<std::uint8_t, 0x8000> internal_ram;
//     std::array<std::uint8_t, 0x8000> mirror_ram_1;
//     std::array<std::uint8_t, 0x8000> mirror_ram_2;
//     std::array<std::uint8_t, 0x8000> mirror_ram_3;
//     std::array<std::uint8_t, 0x0008> ppu_registers;
//     std::array<std::uint8_t, 0x1FF8> mirror_ppu_registers;
//     std::array<std::uint8_t, 0x0018> apu_io_registers;
//     std::array<std::uint8_t, 0x0008> apu_io_disabled;
//     std::array<std::uint8_t, 0xBFE0> other_memory;
//     std::array<std::uint8_t, 0x2000> cartridge_ram;
//     std::array<std::uint8_t, 0x8000> cartridge_rom;
//
//     Memory() : internal_ram{}, mirror_ram_1{}, mirror_ram_2{}, mirror_ram_3{}, ppu_registers{}, mirror_ppu_registers{}, apu_io_registers{}, apu_io_disabled{}, other_memory{}, cartridge_ram{}, cartridge_rom{} {}
//
//     std::uint8_t operator[](const uint16_t address) {
//
//     }
// };


namespace NES {
    class NES {

    public:
        [[noreturn]] void run() {
            // for(;;)
            for(int i = 0; i < 2;i++)
                cpu.run();
        }
        NES() : cpu{memory} {}

        void load_rom(const std::string &rom_path) {
            // Load ROM into memory
            std::ifstream rom_file(rom_path, std::ios::binary);
            if (!rom_file) {
                throw std::runtime_error("Failed to open ROM file");
            }
            rom_file.read(reinterpret_cast<char *>(memory.data()), memory.size());
            std::cout << "Loaded ROM: " << rom_path << std::endl;
            std::cout << "Memory size: " << memory.size() << std::endl;
        }

    private:
        CPU::CPU cpu;
        APU::APU apu;
        PPU::PPU ppu;

        std::array<std::uint8_t, 0xFFFF> memory{};
    };
}

#endif //NES_H
