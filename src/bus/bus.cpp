#include "bus.hpp"
#include "../ppu/ppu.hpp"

#include <algorithm>
#include <assert.h>
#include <stdexcept>

namespace Bus
{
	void Bus::insert_cartridge(std::vector<std::uint8_t> data)
	{
		cartridge = std::make_unique<Cartridge>(data);
	}

	std::uint8_t Bus::cpu_read(const std::uint16_t address)
	{
		// RAM (mirrored every 0x0800)
		if (in_range(address, MemoryRegion::RAM_START, MemoryRegion::RAM_END))
			return ram[address % 0x0800];

		// PPU registers (mirrored every 8 bytes)
		if (in_range(address, MemoryRegion::PPU_REG_START, MemoryRegion::PPU_REG_END)) {
			const std::uint16_t reg = (address - MemoryRegion::PPU_REG_START) % 8 + MemoryRegion::PPU_REG_START;

			assert(ppu != nullptr);

			if (reg == PPU::Registers::STATUS)
				return ppu->read_status();

			if (reg == PPU::Registers::VRAM_DATA)
				return ppu->read_vram_data();

			if (reg == PPU::Registers::OAM_DATA)
				return ppu->read_oam_data();

			return 0x00; // open bus / unused reads
		}

		// Cartridge ROM
		if (in_range(address, MemoryRegion::CART_ROM_START, MemoryRegion::CART_ROM_END))
			return cartridge->map_read(address);

		return 0xFF;
	}

	void Bus::cpu_write(const std::uint16_t address, const std::uint8_t data)
	{
		// RAM
		if (in_range(address, MemoryRegion::RAM_START, MemoryRegion::RAM_END)) {
			ram[address % 0x0800] = data;
			return;
		}

		// PPU registers + DMA
		if (in_range(address, MemoryRegion::PPU_REG_START, MemoryRegion::PPU_REG_END) ||
		    address == PPU::Registers::OAM_DMA) {

			const std::uint16_t reg = (address - MemoryRegion::PPU_REG_START) % 8 + MemoryRegion::PPU_REG_START;

			assert(ppu != nullptr);

			if (reg == PPU::Registers::CONTROLLER)
				ppu->write_ppu_controller(data);

			else if (reg == PPU::Registers::SCROLL)
				ppu->write_ppu_scroll(data);

			else if (reg == PPU::Registers::VRAM_ADDRESS)
				ppu->write_ppu_address(data);

			else if (reg == PPU::Registers::VRAM_DATA)
				ppu->write_vram_data(data);

			else if (reg == PPU::Registers::OAM)
				ppu->write_oam_address(data);

			return;
		}

		// Cartridge RAM
		if (in_range(address, MemoryRegion::CART_RAM_START, MemoryRegion::CART_RAM_END)) {
			cartridge->map_write(address, data);
			return;
		}
	}

	std::uint8_t &Bus::ppu_get_register(const std::uint16_t address)
	{
		if (in_range(address, MemoryRegion::PPU_REG_START, MemoryRegion::PPU_REG_END))
			return ram[address % 8];

		throw std::out_of_range("PPU register address out of range");
	}

	bool Bus::in_range(const std::uint16_t address, const std::uint16_t start, const std::uint16_t end)
	{
		return address >= start && address <= end;
	}

} // namespace Bus
