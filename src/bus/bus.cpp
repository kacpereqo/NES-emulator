#include "bus.hpp"
#include "../ppu/ppu.hpp"

#include <algorithm>
#include <assert.h>
#include <stdexcept>

namespace Bus {
    Bus::Bus(std::array<std::uint8_t, 0x10000> &data, PPU::PPU &ppu)
        : ppu(ppu) {
        std::copy(data.begin(), data.begin() + 0x0800, ram.begin());
        std::copy(data.begin() + 0x8000, data.begin() + 0x10000, rom.begin());
    }

    std::uint8_t Bus::cpu_read(const std::uint16_t address) {
    	if (in_range(address, 0x0000, 0x1FFF)) {
    		return ram[address % 0x0800];
        }

    	if (in_range(address, 0x2000, 0x3FFF)) {

    		assert(address != PPU::Registers::CONTROLLER &&
				   address != PPU::Registers::MASK &&
				   address != PPU::Registers::OAM &&
				   address != PPU::Registers::SCROLL &&
				   address != PPU::Registers::VRAM_ADDRESS
				   );

    		// Reading from $2002 (PPUSTATUS) resets the internal latch used by $2005 and $2006

    		if (address == PPU::Registers::STATUS)
    			return ppu.read_status();

    		if (address == PPU::Registers::VRAM_DATA)
    			return ppu.read_vram_data();

    		if (address == PPU::Registers::OAM_DATA)
    			return ppu.read_oam_data();
    	}

        if (in_range(address, 0x8000, 0xFFFF))
            return rom[address - 0x8000];

        return 0xFF;
    }

    void Bus::cpu_write(const std::uint16_t address, const std::uint8_t data) {
    	if (in_range(address, 0x0000, 0x1FFF)) {
    		ram[address % 0x0800] = data;
    		return;
    	}

        if (in_range(address, 0x2000, 0x3FFF) || address == PPU::Registers::OAM_DMA) {
        	assert(address != PPU::Registers::STATUS &&
				   address != PPU::Registers::OAM_DATA &&
				   address != PPU::Registers::OAM_DMA);

        	if (address == PPU::Registers::CONTROLLER)
				ppu.write_ppu_controller(data);

			else if (address == PPU::Registers::SCROLL)
				ppu.write_ppu_scroll(data);

        	else if (address == PPU::Registers::VRAM_ADDRESS)
        		ppu.write_ppu_address(data);

        	else if (address == PPU::Registers::VRAM_DATA)
				ppu.write_vram_data(data);

        	else if (address == PPU::Registers::OAM)
        		ppu.write_oam_address(data);
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
