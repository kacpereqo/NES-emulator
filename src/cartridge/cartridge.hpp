//
// Created by debilian on 24.03.2026.
//

#pragma once

#include <cassert>
#include <cstring>
#include <memory>
#include <vector>

#include "../mapper/ines_header.hpp"
#include "../mapper/mapper.hpp"
#include "../mapper/nrom.hpp"


class Cartridge
{
public:

	explicit Cartridge(std::vector<std::uint8_t> data)
	{
		std::size_t size = data.size();

		INesHeader::Header header{};
		memcpy(&header, data.data(), sizeof(header));

		const std::uint32_t prg_rom_size = header.size_of_prg_rom * 16 * 1024;
		const std::uint32_t chr_rom_size = header.size_of_prg_rom * 8 * 1024;

		const std::uint8_t mapperNumber = ((header.flags_7 & INesHeader::flag7::MapperUpperNibble) >> 4)
										| (header.flags_6 & INesHeader::flag6::MapperLowerNibble);

		this->prg_rom.resize(prg_rom_size);
		this->chr_rom.resize(chr_rom_size);

		this->mapper = this->get_mapper_by_id(mapperNumber);

		std::size_t offset = 16;
		if (header.flags_6 & INesHeader::flag6::TrainerPresent)
			offset += 512;

		std::copy(data.begin() + offset, data.begin() + offset + prg_rom_size, prg_rom.begin());
		offset += prg_rom_size;

		if (chr_rom_size > 0)
			std::copy(data.begin() + offset, data.begin() + offset + chr_rom_size, chr_rom.begin());
	}

	std::uint8_t map_read(std::uint16_t address)
	{
		assert(mapper!=nullptr);

		return mapper->map_cpu_read(address);
	}
	void map_write(std::uint16_t address, std::uint8_t data)
	{
		assert(mapper!=nullptr);

		mapper->map_cpu_write(address, data);
	}

private:
	std::unique_ptr<Mapper::Mapper> get_mapper_by_id(const std::uint8_t mapper_number)
	{
		switch (mapper_number) {
			case (Mapper::MapperId::NROM): return std::make_unique<Mapper::NROM>(prg_rom, prg_ram);
			default: throw;
		}
	}

	std::vector<std::uint8_t> prg_rom;
	std::vector<std::uint8_t> chr_rom;
	std::vector<std::uint8_t> prg_ram;

	std::unique_ptr<Mapper::Mapper> mapper;
};