#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include "enums.hpp"

namespace Bus {
  class Bus;   // forward declaration
}

namespace PPU {

  class PPU {
  public:
    explicit PPU(Bus::Bus& bus);

    void init();
    void load_chr_rom(std::vector<std::uint8_t>&& chr_rom);

    void run();

    void vram_address_increment() const;

    void latch_set();
    void latch_reset();

  private:
    bool latch{false};

    std::uint8_t& register_controller;   // $2000
    std::uint8_t& register_mask;         // $2001
    std::uint8_t& register_status;       // $2002
    std::uint8_t& register_oam_address;  // $2003
    std::uint8_t& register_oam_data;     // $2004
    std::uint8_t& register_scroll;       // $2005
    std::uint8_t& register_vram_address; // $2006
    std::uint8_t& register_vram_data;    // $2007
    std::uint8_t& register_oam_dma;      // $4014

    std::uint16_t ppu_address{0};
    std::uint16_t ppu_scroll{0};

    std::array<std::uint8_t, VRAM_SIZE> vram{};
    std::array<std::uint8_t, OAM_SIZE> states{};
    std::array<std::uint8_t, CHR_ROM_SIZE> palette{};

    std::vector<std::uint8_t> chr_rom{};
  };

}