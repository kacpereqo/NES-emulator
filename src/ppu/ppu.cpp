#include "ppu.hpp"
#include "../bus/bus.hpp"

namespace PPU {

    PPU::PPU(Bus::Bus& bus)
        : register_controller{bus.ppu_get_register(Registers::CONTROLLER)},
          register_mask{bus.ppu_get_register(Registers::MASK)},
          register_status{bus.ppu_get_register(Registers::STATUS)},
          register_oam_address{bus.ppu_get_register(Registers::OAM)},
          register_oam_data{bus.ppu_get_register(Registers::OAM_DATA)},
          register_scroll{bus.ppu_get_register(Registers::SCROLL)},
          register_vram_address{bus.ppu_get_register(Registers::VRAM_ADDRESS)},
          register_vram_data{bus.ppu_get_register(Registers::VRAM_DATA)},
          register_oam_dma{bus.ppu_get_register(Registers::OAM_DMA)}
    {
    }

    void PPU::init() {}

    void PPU::load_chr_rom(std::vector<std::uint8_t>&& chr_rom) {
        this->chr_rom = std::move(chr_rom);
    }

    void PPU::run() {}

    void PPU::vram_address_increment() const {
        if (register_controller & Controller::Increment)
            register_vram_address += 32;
        else
            register_vram_address += 1;
    }



    void PPU::latch_set() {
        latch = true;
    }

    void PPU::latch_reset() {
        latch = false;
    }

}