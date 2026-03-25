#pragma once

#include <cstdint>

namespace Bus
{
	class AbstractBus
	{
	public:
		virtual ~AbstractBus() = default;

		virtual std::uint8_t cpu_read(std::uint16_t address)                     = 0;
		virtual void         cpu_write(std::uint16_t address, std::uint8_t data) = 0;
	};
} // namespace Bus
