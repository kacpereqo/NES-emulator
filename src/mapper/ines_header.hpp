#pragma once
#include <array>
#include <cstdint>

namespace INesHeader
{
	// --------------------
	// iNES Header structure
	struct Header
	{
		std::array<char, 4>         signature;       // "NES" + 0x1A
		std::uint8_t                size_of_prg_rom; // 16 KB units
		std::uint8_t                size_of_chr_rom; // 8 KB units (0 = CHR RAM)
		std::uint8_t                flags_6;
		std::uint8_t                flags_7;
		std::uint8_t                flags_8;
		std::uint8_t                flags_9;
		std::uint8_t                flags_10;
		std::array<std::uint8_t, 5> reserved;
	};

	enum class Mirroring : std::uint8_t
	{
		Vertical   = 0,
		Horizontal = 1,
	};

	// --------------------
	// Flags 6 – mirroring, battery, trainer, mapper low nibble
	namespace flag6
	{
		enum flag6 : uint8_t
		{
			Mirroring         = 1 << 0, // bit 0 – vertical/horizontal
			BatteryPRG_RAM    = 1 << 1, // bit 1 – battery-backed PRG RAM
			TrainerPresent    = 1 << 2, // bit 2 – 512-byte trainer
			FourScreen        = 1 << 3, // bit 3 – four-screen layout
			MapperLowerNibble = 0xF0    // bits 4–7 – lower mapper nibble
		};
	}

	// --------------------
	// Flags 7 – VS/PlayChoice/NES2.0, mapper upper nibble
	namespace flag7
	{
		enum flag7 : uint8_t
		{
			VS_Unisystem      = 1 << 0, // bit 0 – VS Unisystem
			PlayChoice_10     = 1 << 1, // bit 1 – PlayChoice-10
			NES2_0_Format     = 1 << 2, // bit 2 – NES 2.0 format
			MapperUpperNibble = 0xF0    // bits 4–7 – upper mapper nibble
		};
	}

	// --------------------
	// Flags 8 – PRG RAM size in 8 KB units
	namespace flag8
	{
		enum flag8 : uint8_t
		{
			PRG_RAM_8KB   = 0, // default
			PRG_RAM_16KB  = 2,
			PRG_RAM_32KB  = 4,
			PRG_RAM_64KB  = 8,
			PRG_RAM_128KB = 16
		};
	}

	// --------------------
	// Flags 9 – TV system
	namespace flag9
	{
		enum flag9 : uint8_t
		{
			TV_NTSC   = 0,
			TV_PAL    = 1,
			TV_Dual_0 = 2,
			TV_Dual_1 = 3
		};
	}

	// --------------------
	// Flags 10 – unofficial extensions
	namespace flag10
	{
		enum flag10 : uint8_t
		{
			TVSystem       = 1 << 0, // bit 0 – 0=NTSC, 1=PAL
			PRG_RAMPresent = 1 << 1, // bit 1 – 0=present, 1=not present
			BusConflicts   = 1 << 2  // bit 2 – 0=no conflicts, 1=conflicts
		};
	}
} // namespace INesHeader
