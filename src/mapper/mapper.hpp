//
// Created by remza on 13.05.2025.
//

#pragma once

#include <cstdint>



namespace Mapper {
    class Mapper {
    public:
        virtual ~Mapper() = default;

        virtual std::uint8_t map_cpu_read(std::uint16_t address) = 0;
        virtual void map_cpu_write(std::uint16_t address, std::uint8_t data) = 0;
    };

	namespace MapperId
	{
		enum MapperId : std::uint8_t
		{
			NROM = 0
		};
	}


} // namespace Cartridge