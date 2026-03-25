#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include "../cartridge/cartridge.hpp"
#include "abstract_bus.hpp"

namespace PPU
{
	class PPU;
}

namespace Bus
{

	/*
	Address Range    Size    Device
	------------------------------------------------------------
	$0000–$07FF      $0800   2 KB internal RAM
	$0800–$0FFF      $0800   Mirrors of $0000–$07FF
	$1000–$17FF      $0800   Mirrors of $0000–$07FF
	$1800–$1FFF      $0800   Mirrors of $0000–$07FF

	$2000–$2007      $0008   NES PPU registers
	$2008–$3FFF      $1FF8   Mirrors of $2000–$2007 (every 8 bytes)
	$4000–$4017      $0018   NES APU and I/O registers
	$4018–$401F      $0008   Disabled APU/I/O (test mode)

	$4020–$5FFF      $1FE0   Cartridge space (typically unmapped)
	$6000–$7FFF      $2000   Cartridge RAM (if present)
	$8000–$FFFF      $8000   Cartridge ROM + mapper registers
	------------------------------------------------------------
	*/

	namespace MemoryRegion
	{
		// Internal RAM
		constexpr std::uint16_t RAM_START = 0x0000;
		constexpr std::uint16_t RAM_END   = 0x1FFF;

		// PPU registers
		constexpr std::uint16_t PPU_REG_START = 0x2000;
		constexpr std::uint16_t PPU_REG_END   = 0x3FFF;

		// APU and I/O
		constexpr std::uint16_t APU_IO_START = 0x4000;
		constexpr std::uint16_t APU_IO_END   = 0x4017;

		// Disabled/test range
		constexpr std::uint16_t TEST_START = 0x4018;
		constexpr std::uint16_t TEST_END   = 0x401F;

		// Cartridge space
		constexpr std::uint16_t CART_START = 0x4020;
		constexpr std::uint16_t CART_END   = 0xFFFF;

		// Optional finer breakdown
		constexpr std::uint16_t CART_RAM_START = 0x6000;
		constexpr std::uint16_t CART_RAM_END   = 0x7FFF;

		constexpr std::uint16_t CART_ROM_START = 0x8000;
		constexpr std::uint16_t CART_ROM_END   = 0xFFFF;
	} // namespace MemoryRegion

	class Bus final : public AbstractBus
	{
	public:
		void insert_cartridge(std::vector<std::uint8_t> data);
		void connect_ppu(PPU::PPU &ppu)
		{
			this->ppu = &ppu;
		}

		// Asserts due to R/W permissions
		// https://www.nesdev.org/wiki/PPU_registers#Summary

		std::uint8_t cpu_read(std::uint16_t address) override;
		void         cpu_write(std::uint16_t address, std::uint8_t data) override;

		std::uint8_t          ppu_read_chr_rom(std::uint16_t address);
		std::uint8_t         &ppu_get_register(std::uint16_t address);
		INesHeader::Mirroring get_cartrdige_mirroring();

	private:
		static bool in_range(std::uint16_t address, std::uint16_t start, std::uint16_t end);

		PPU::PPU *ppu = nullptr;

		std::unique_ptr<Cartridge> cartridge;

		std::array<std::uint8_t, 0x800> ram{};
	};
} // namespace Bus
