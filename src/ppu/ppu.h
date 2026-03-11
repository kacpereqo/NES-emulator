//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef PPU_H
#define PPU_H

#include "../bus/bus.hpp"
#include "enums.hpp"
#include <vector>

namespace PPU {


class PPU {
public:
  explicit PPU(Bus::Bus &bus)
      : register_controller{bus.ppu_get_register(Registers::CONTROLLER)},
        register_mask{bus.ppu_get_register(Registers::MASK)},
        register_status{bus.ppu_get_register(Registers::STATUS)},
        register_oam_address{bus.ppu_get_register(Registers::OAM)},
        register_oam_data{bus.ppu_get_register(Registers::OAM_DATA)},
        register_scroll{bus.ppu_get_register(Registers::SCROLL)},
        register_vram_address{bus.ppu_get_register(Registers::VRAM_ADDRESS)},
        register_vram_data{bus.ppu_get_register(Registers::VRAM_DATA)},
        register_oam_dma{bus.ppu_get_register(Registers::OAM_DATA)}
  {}

  void init() { ; }
  void load_chr_rom(std::vector<std::uint8_t> &&chr_rom) {
    this->chr_rom = chr_rom;
  }

  void run() {

  }

  void vram_address_increment() {
    if (this->register_controller & Controller::Increment)
      this->register_vram_address += 32;
    else
      this->register_vram_address += 1;
  }

private:
  std::uint8_t &register_controller;   // $2000
  std::uint8_t &register_mask;         // $2001
  std::uint8_t &register_status;       // $2002
  std::uint8_t &register_oam_address;  // $2003
  std::uint8_t &register_oam_data;     // $2004
  std::uint8_t &register_scroll;       // $2005
  std::uint8_t &register_vram_address; // $2006
  std::uint8_t &register_vram_data;    // $2007
  std::uint8_t &register_oam_dma;      // $4014

  std::uint16_t ppu_address = 0;
  std::uint16_t ppu_scroll  = 0;

  std::array<std::uint8_t, VRAM_SIZE> vram{};       // background data
  std::array<std::uint8_t, OAM_SIZE> states{};      // state of the sprites
  std::array<std::uint8_t, CHR_ROM_SIZE> palette{}; // palette data

  std::vector<std::uint8_t> chr_rom{}; // Character ROM data
}; // namespace class PPU
} // namespace PPU

#endif // PPU_H
