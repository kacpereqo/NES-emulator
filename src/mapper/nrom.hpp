#pragma once

#include <cstdint>
#include <vector>
#include "mapper.hpp"

namespace Mapper
{
	class NROM : public Mapper
	{
	public:
		NROM(std::vector<std::uint8_t> &prg, std::vector<std::uint8_t> &ram, std::vector<std::uint8_t> &chr) :
		    prg_rom(prg), prg_ram(ram), chr_rom(chr)
		{}

		std::uint8_t map_cpu_read(std::uint16_t address) override
		{
			if (address >= 0x6000 && address <= 0x7FFF) {
				// PRG RAM
				return prg_ram[address - 0x6000];
			}
			if (address >= 0x8000 && address <= 0xFFFF) {
				std::size_t prg_size    = prg_rom.size();
				std::size_t mapped_addr = address - 0x8000;

				if (prg_size == 0x4000) // 16 KB PRG ROM
					mapped_addr %= 0x4000;

				return prg_rom[mapped_addr];
			}

			// Default return for unmapped addresses
			return 0;
		}

		void map_cpu_write(std::uint16_t address, std::uint8_t data) override
		{
			if (address >= 0x6000 && address <= 0x7FFF)
				prg_ram[address - 0x6000] = data;
		}

		std::uint8_t read_chr_rom(std::uint16_t address) override
		{
			return prg_ram[address];
		}

	private:
		std::vector<std::uint8_t> &prg_rom;
		std::vector<std::uint8_t> &prg_ram;
		std::vector<std::uint8_t> &chr_rom;
	};
} // namespace Mapper
