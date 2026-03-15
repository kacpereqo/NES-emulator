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

  class PPU {
  public:
    explicit PPU(Bus::Bus &bus, CPU::CPU& cpu);

    void init();

    void load_chr_rom(std::vector<std::uint8_t> &&chr_rom);

    void run();

    void vram_address_increment() const;

    void latch_set();
    void latch_reset();

    void signal_write_ppu_controller();
    void signal_write_ppu_address();
    void signal_write_ppu_scroll();

    void send_nmi_interrupt() const;

  private:
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

    std::array<std::uint8_t, VRAM_SIZE> vram{};
    std::array<Sprite, OAM_SIZE/sizeof(Sprite)> states{};
    std::array<std::uint8_t, CHR_ROM_SIZE> palette{};

    std::vector<std::uint8_t> chr_rom{};
  };
}
