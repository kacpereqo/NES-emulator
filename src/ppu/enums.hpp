//
// Created by remza on 04.05.2025.
//

#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <cstdint>

namespace PPU
{

	struct Sprite
	{
		std::uint8_t pos_y;
		std::uint8_t index;
		std::uint8_t attributes;
		std::uint8_t byte_x;
	};

	struct Palette
	{
		std::array<std::uint8_t, 4> colors{};
	};

	struct Nametable
	{
		std::array<std::uint8_t, 960> data{};
		std::array<std::uint8_t, 64>  attribute_table{};
	};

	constexpr std::uint16_t VRAM_SIZE{sizeof(Nametable) * 4}; // 2KB of VRAM
	constexpr std::uint16_t OAM_SIZE{0x100};                  // 256 bytes of OAM
	constexpr std::uint16_t CHR_ROM_SIZE{0x2000};             // 8KB of CHR ROM
	constexpr std::uint16_t PALETTE_SIZE{0x20};               // 32 bytes of palette RAM

	namespace Registers
	{
		constexpr std::uint16_t CONTROLLER{0x2000};
		constexpr std::uint16_t MASK{0x2001};
		constexpr std::uint16_t STATUS{0x2002};
		constexpr std::uint16_t OAM{0x2003};
		constexpr std::uint16_t OAM_DATA{0x2004};
		constexpr std::uint16_t SCROLL{0x2005};
		constexpr std::uint16_t VRAM_ADDRESS{0x2006};
		constexpr std::uint16_t VRAM_DATA{0x2007};
		constexpr std::uint16_t OAM_DMA{0x4014};
		constexpr std::uint16_t PALETTE{0x3F00};
	} // namespace Registers

	/// PPUCTRL
	// 7  bit  0
	// ---- ----
	// VPHB SINN
	// |||| ||||
	// |||| ||++- Base nametable address
	// |||| ||    (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
	// |||| |+--- VRAM address increment per CPU read/write of PPUDATA
	// |||| |     (0: add 1, going across; 1: add 32, going down)
	// |||| +---- Sprite pattern table address for 8x8 sprites
	// ||||       (0: $0000; 1: $1000; ignored in 8x16 mode)
	// |||+------ Background pattern table address (0: $0000; 1: $1000)
	// ||+------- Sprite size (0: 8x8 pixels; 1: 8x16 pixels – see PPU OAM#Byte 1)
	// |+-------- PPU master/slave select
	// |          (0: read backdrop from EXT pins; 1: output color on EXT pins)
	// +--------- Vblank NMI enable (0: off, 1: on)

	namespace Controller
	{
		enum Controller : std::uint8_t
		{
			/// $2000
			NMI                      = 1 << 7,   // Generate NMI at the start of the frame
			Master_slave             = 1 << 6,   // PPU master/slave
			Sprite_size              = 1 << 5,   // Sprite height (8x8 or 8x16)
			Background_tile_selected = 1 << 4,   // Background tile select
			Sprite_tile_selected     = 1 << 3,   // Sprite tile select
			Increment                = 1 << 2,   // VRAM address increment per CPU read/write
			Nametable                = 0b11 << 0 // Nametable select (2 bits)
		};
	}
} // namespace PPU

/// PPUMASK
namespace Mask
{
	enum Mask : std::uint8_t
	{
		/// $2001
		Emphasize_blue       = 1 << 7, // Color emphasis - blue
		Emphasize_green      = 1 << 6, // Color emphasis - green
		Emphasize_red        = 1 << 5, // Color emphasis - red
		Show_sprites         = 1 << 4, // Show sprites
		Show_background      = 1 << 3, // Show background
		Show_sprites_left    = 1 << 2, // Show sprites in leftmost 8 pixels
		Show_background_left = 1 << 1, // Show background in leftmost 8 pixels
		Greyscale            = 1 << 0  // Greyscale mode
	};
}

/// PPUSTATUS
namespace Status
{
	enum Status : std::uint8_t
	{
		/// $2002 (read-only)
		VBlank          = 1 << 7, // Vertical blank started
		Sprite0_hit     = 1 << 6, // Sprite 0 hit
		Sprite_overflow = 1 << 5  // Sprite overflow
		                          // Lower 5 bits are unused
	};
}

namespace OAM::Attributes
{
	enum Attributes : std::uint8_t
	{
		palette  = 0b11,   // Bits 0-1: Palette (4 to 7) of sprite
		priority = 1 << 5, // Bit 5: Sprite-to-background priority (0: in front of background; 1: behind background)
		flip_horizontal = 1 << 6, // Bit 6: Flip sprite horizontally
		flip_vertical   = 1 << 7  // Bit 7: Flip sprite vertically
	};
}

// namespace PPU

#endif // ENUMS_HPP
