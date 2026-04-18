#include "ppu.hpp"
#include "../bus/bus.hpp"

namespace PPU
{
	PPU::PPU(Bus::Bus &bus, CPU::CPU &cpu) :
	    register_controller{bus.ppu_get_register(Registers::CONTROLLER)},
	    register_mask{bus.ppu_get_register(Registers::MASK)},
	    register_status{bus.ppu_get_register(Registers::STATUS)},
	    register_oam_address{bus.ppu_get_register(Registers::OAM)},
	    register_oam_data{bus.ppu_get_register(Registers::OAM_DATA)},
	    register_scroll{bus.ppu_get_register(Registers::SCROLL)},
	    register_vram_address{bus.ppu_get_register(Registers::VRAM_ADDRESS)},
	    register_vram_data{bus.ppu_get_register(Registers::VRAM_DATA)},
	    register_oam_dma{bus.ppu_get_register(Registers::OAM_DMA)},
	    cpu(cpu),
	    bus(bus)
	{}

	void PPU::init()
	{}

	void PPU::run()
	{


		if (this->register_controller & Controller::NMI && this->scanline == 241 && this->cycle == 1)
			this->cpu.signal_nmi_interrupt();
	    
		if (this->cycle >= 1 && this->cycle <= 256) {
			const std::uint16_t base_nametable_address           = this->get_base_nametable_adress();
			const std::uint16_t sprite_pattern_table_address     = this->get_sprite_pattern_table_adress();
			const std::uint16_t background_pattern_Table_address = this->get_background_pattern_table_address();
		}

		this->cycle++;
		if (this->cycle > 340) {
			this->cycle = 0;
			this->scanline++;
		}

		if (this->scanline == 241 && this->cycle == 1)
			this->register_status |= Status::VBlank;

		if (this->scanline == 261 && this->cycle == 1)
			this->register_status &= ~Status::VBlank;

		if (this->scanline > 261)
			this->scanline = 0;
	}

	void PPU::vram_address_increment()
	{
		if (register_controller & Controller::Increment)
			current_vram_address += 32;
		else
			current_vram_address += 1;
	}

	std::uint16_t PPU::get_scanline()
	{
		return this->scanline;
	}
	std::uint16_t PPU::get_cycle()
	{
		return this->cycle;
	}

} // namespace PPU

void PPU::PPU::write_ppu_address(uint8_t data)
{
	if (!latch)
		this->temp_vram_address = (data & 0x3F) << 8;
	else {
		this->temp_vram_address |= data;
		this->current_vram_address = this->temp_vram_address;
	}

	latch = !latch;

	this->register_vram_address = this->temp_vram_address;
}

void PPU::PPU::write_ppu_controller(std::uint8_t data)
{

	const bool old_nmi = this->register_controller & Controller::NMI;
	const bool new_nmi = data & Controller::NMI;

	if (new_nmi && !old_nmi) {
		if (this->register_status & Status::VBlank)
			this->cpu.signal_nmi_interrupt();
	}

	// Set new controller nametable to t (temp_vram_address) register
	// https://www.nesdev.org/wiki/PPU_registers#PPUADDR

	const std::uint8_t nametables = data & Controller::Nametable;
	this->temp_vram_address       = (this->temp_vram_address & 0xF3FF) | (nametables << 10);

	this->register_controller = data;
}

std::uint8_t PPU::PPU::read_status()
{
	std::uint8_t data = this->register_status;

	this->register_status &= ~Status::VBlank;
	this->latch = false;

	return data;
}

void PPU::PPU::write_ppu_scroll(uint8_t data)
{
	latch                 = !latch;
	this->register_scroll = data;
}

void PPU::PPU::write_vram_data(std::uint8_t data)
{
	vram[current_vram_address % VRAM_SIZE] = data;
	vram_address_increment();
}

std::uint8_t PPU::PPU::read_oam_data()
{
	return this->oam[register_oam_address];
}
std::uint8_t PPU::PPU::read_vram_data()
{
	return vram[this->map_vram_mirroring(current_vram_address)];
}

void PPU::PPU::write_oam_address(std::uint8_t data)
{
	this->register_oam_address = data;
}
void PPU::PPU::write_ppu_mask(std::uint8_t data)
{
	this->register_mask = data;
}
void PPU::PPU::write_oam_data(std::uint8_t data)
{
	this->oam[register_oam_address++] = data;
}

void PPU::PPU::write_oam_dma(std::uint8_t data)
{
	const std::uint16_t cpu_start_address = data << 8;

	for (size_t i = 0; i < 0x100; i++) {
		oam[register_oam_address] = bus.cpu_read(cpu_start_address + i);
		register_oam_address      = (register_oam_address + 1) & 0xFF;
	}
}

std::uint16_t PPU::PPU::map_vram_mirroring(const std::uint16_t vram_address)
{
	assert(vram_address >= 0x2000 && vram_address < 0x3000);

	INesHeader::Mirroring mirroring = bus.get_cartrdige_mirroring();

	if (mirroring == INesHeader::Mirroring::Horizontal) {
		if (vram_address >= 0x2000 && vram_address < 0x2400)
			return vram_address - 0x2000;

		if (vram_address >= 0x2400 && vram_address < 0x2800)
			return vram_address - 0x2000;

		if (vram_address >= 0x2800 && vram_address < 0x2C00)
			return vram_address - 0x2000 + sizeof(Nametable);

		if (vram_address >= 0x2C00 && vram_address < 0x3000)
			return vram_address - 0x2000 + sizeof(Nametable);
	}

	else if (mirroring == INesHeader::Mirroring::Vertical) {
		if (vram_address >= 0x2000 && vram_address < 0x2400)
			return vram_address - 0x2000;

		if (vram_address >= 0x2400 && vram_address < 0x2800)
			return vram_address - 0x2000 + sizeof(Nametable);

		if (vram_address >= 0x2800 && vram_address < 0x2C00)
			return vram_address - 0x2000;

		if (vram_address >= 0x2C00 && vram_address < 0x3000)
			return vram_address - 0x2000 + sizeof(Nametable);
	}
	return 0x0;
}

std::uint16_t PPU::PPU::get_base_nametable_adress() const
{
	std::uint8_t value = this->register_status & Controller::Nametable;

	switch (value) {
		case 0:
			return 0x2000;
		case 1:
			return 0x2400;
		case 2:
			return 0x2800;
		case 3:
			return 0x2C00;
		default:;
	}
	return {};
}

std::uint16_t PPU::PPU::get_sprite_pattern_table_adress() const
{
	std::uint8_t value = this->register_status & Controller::Sprite_tile_selected;

	switch (value) {
		case 0:
			return 0x0000;
		case 1:
			return 0x1000;
		default:;
	}

	return {};
}

std::uint16_t PPU::PPU::get_background_pattern_table_address() const
{
	std::uint8_t value = this->register_status & Controller::Background_tile_selected;

	switch (value) {
		case 0:
			return 0x0000;
		case 1:
			return 0x1000;
		default:;
	}

	return {};
}
