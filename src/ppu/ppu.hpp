#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include "enums.hpp"
#include "../cpu/cpu.h"

namespace Bus {
  class Bus; // forward declaration
}

namespace PPU {

  struct Sprite {
    std::uint8_t pos_y;
    std::uint8_t index;
    std::uint8_t attributes;
    std::uint8_t byte_x;
  };

	struct Palette
	{
		std::array<std::uint8_t, 4> colors{};
	};

	struct Nametable
	{
		std::array<std::uint8_t, 960> data{};
		std::array<std::uint8_t, 64> attribute_table{};
	};

  class PPU {
  public:
    explicit PPU(Bus::Bus &bus, CPU::CPU& cpu);

    void init();

    void load_chr_rom(std::vector<std::uint8_t> &&chr_rom);

    void run();

    void vram_address_increment();

  	void write_vram_data(std::uint8_t data);
	void write_ppu_scroll(std::uint8_t data);
    void write_ppu_address(std::uint8_t data);
  	void write_ppu_controller(std::uint8_t data);
  	void write_oam_address(std::uint8_t data);

  	std::uint8_t read_status();
  	std::uint8_t read_oam_data();
  	std::uint8_t read_vram_data();

private:
  	uint32_t cycle {0};
  	uint32_t scanline {0};

    CPU::CPU& cpu;

    // Memory registers
    std::uint8_t &register_controller; // $2000
    std::uint8_t &register_mask; // $2001
    std::uint8_t &register_status; // $2002
    std::uint8_t &register_oam_address; // $2003
    std::uint8_t &register_oam_data; // $2004
    std::uint8_t &register_scroll; // $2005
    std::uint8_t &register_vram_address; // $2006
    std::uint8_t &register_vram_data; // $2007
    std::uint8_t &register_oam_dma; // $4014

    // Internal registers
    // https://www.nesdev.org/wiki/PPU_programmer_reference#Internal_registers

    std::uint16_t current_vram_address : 15 {0}; // v
    std::uint16_t temp_vram_address : 15 {0};    // t
    std::uint8_t fine_x_scroll : 3 {0};          // x
    bool latch{false};                           // w


    std::array<std::uint8_t, VRAM_SIZE/sizeof(Nametable)> vram{}; // background infromation
    std::array<Sprite, OAM_SIZE/sizeof(Sprite)> oam{}; // state of sprites
    std::array<std::uint8_t, CHR_ROM_SIZE> chr_rom{}; // tile data is stored in CHR ROM, but palette data is stored in RAM, so we can write to it
  	std::array<std::uint8_t, PALETTE_SIZE> palette; // pallets used by a screen
  };
}
