//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef PPU_H
#define PPU_H

#include "enums.hpp"
#include <vector>

namespace PPU {

constexpr std::uint16_t VRAM_SIZE{0x800};     // 2KB of VRAM
constexpr std::uint16_t OAM_SIZE{0x100};      // 256 bytes of OAM
constexpr std::uint16_t CHR_ROM_SIZE{0x2000}; // 8KB of CHR ROM

class PPU {
public:
  explicit PPU(std::array<std::uint8_t, 0xFFFF> &memory)
      : controller{memory[0x2000]}, mask{memory[0x2001]},
        status{memory[0x2002]}, oam_address{memory[0x2003]},
        oam_data{memory[0x2004]}, scroll{memory[0x2005]},
        vram_address{memory[0x2006]}, vram_data{memory[0x2007]},
        oam_dma{memory[0x4014]} {}

  void init() { ; }
  void load_chr_rom(std::vector<std::uint8_t> &&chr_rom) {
    this->chr_rom = chr_rom;
  }

  void run() { ; }

  void vram_address_increment() {
    if (this->controller & Controller::Increment)
      this->vram_address += 32;
    else
      this->vram_address += 1;
  }

private:
  std::uint8_t &controller;   // $2000
  std::uint8_t &mask;         // $2001
  std::uint8_t &status;       // $2002
  std::uint8_t &oam_address;  // $2003
  std::uint8_t &oam_data;     // $2004
  std::uint8_t &scroll;       // $2005
  std::uint8_t &vram_address; // $2006
  std::uint8_t &vram_data;    // $2007
  std::uint8_t &oam_dma;      // $4014

  std::array<std::uint8_t, VRAM_SIZE> vram{};       // background data
  std::array<std::uint8_t, OAM_SIZE> states{};      // state of the sprites
  std::array<std::uint8_t, CHR_ROM_SIZE> palette{}; // palette data

  std::vector<std::uint8_t> chr_rom{}; // Character ROM data
};                                     // namespace class PPU
} // namespace PPU

#endif // PPU_H
