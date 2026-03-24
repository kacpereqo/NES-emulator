//
// Created by thinkPaździerż on 19.04.2025.
//

#include "cpu.h"
#include <iostream>

#include "../ppu/enums.hpp"

void CPU::CPU::init() {
    const std::uint8_t reset_vector_low = this->bus.cpu_read(0xFFFC);
    const std::uint8_t reset_vector_high = this->bus.cpu_read(0xFFFD);

    this->PC = reset_vector_low | (reset_vector_high << 8);
}

void CPU::CPU::nmi_handler() {
    constexpr std::uint16_t NMI_VECTOR = 0xFFFA;

    push_to_stack(this->PC);
    push_to_stack(static_cast<uint16_t>(this->P & ~ProcessorStatus::BreakCommand));

    this->P |= ProcessorStatus::InterruptDisable;

    const std::uint8_t low = bus.cpu_read(NMI_VECTOR);
    const std::uint8_t high = bus.cpu_read(NMI_VECTOR + 1);

    const std::uint16_t nmi_address = (high << 8) | low;
    this->PC = nmi_address;
}

void CPU::CPU::signal_nmi_interrupt() {
    this->is_nmi_pending = true;
}

void CPU::CPU::run() {
    // if (this->cpu_cycle_delay == 0) {
    //
    //     if (is_nmi_pending) {
    //         this->is_nmi_pending = false;
    //         this->nmi_handler();
    //         this->cpu_cycle_delay = 7;
    //     }

        // else {
    const std::uint8_t opcode = this->bus.cpu_read(PC++);

    const auto [instruction_handler, addressing_mode_handler, cycles] = instruction_set[opcode];

    (this->*addressing_mode_handler)();
    (this->*instruction_handler)();
    this->cpu_cycle_delay = cycles;
        // }
    // }

    // this->cpu_cycle_delay--;
}

void CPU::CPU::addressing_accumulator() { this->temp_value = this->A; }

void CPU::CPU::addressing_absolute() {
    this->temp_address =
            this->bus.cpu_read(this->PC) | (this->bus.cpu_read(this->PC + 1) << 8);
    this->temp_value = this->bus.cpu_read(this->temp_address);
    this->PC += 2;
}

void CPU::CPU::addressing_absolute_x() {
    this->temp_address =
            (this->bus.cpu_read(this->PC) | (this->bus.cpu_read(this->PC + 1) << 8)) +
            this->X;
    this->temp_value = this->bus.cpu_read(this->temp_address);
    this->PC += 2;
}

void CPU::CPU::addressing_absolute_y() {
    this->temp_address =
            (this->bus.cpu_read(this->PC) | (this->bus.cpu_read(this->PC + 1) << 8)) +
            this->Y;
    this->temp_value = this->bus.cpu_read(this->temp_address);
    this->PC += 2;
}

void CPU::CPU::addressing_immediate() {
    this->temp_value = this->bus.cpu_read(this->PC++);
}

void CPU::CPU::addressing_implied() { ; }

void CPU::CPU::addressing_indirect() {
	const std::uint8_t pointer_low_byte = this->bus.cpu_read(this->PC++);
	const std::uint8_t pointer_high_byte = this->bus.cpu_read(this->PC++);

	const std::uint16_t pointer_address =
		static_cast<std::uint16_t>(pointer_low_byte) |
		(static_cast<std::uint16_t>(pointer_high_byte) << 8);

	const std::uint8_t target_low_byte = this->bus.cpu_read(pointer_address);

	const std::uint16_t target_high_byte_address =
		(pointer_address & 0xFF00) | static_cast<std::uint8_t>(pointer_address + 1);

	const std::uint8_t target_high_byte = this->bus.cpu_read(target_high_byte_address);

	this->temp_address =
		static_cast<std::uint16_t>(target_low_byte) |
		(static_cast<std::uint16_t>(target_high_byte) << 8);
}

void CPU::CPU::addressing_indirect_x() {
    this->temp_address = (this->bus.cpu_read(this->PC++) + this->X) & 0xFF;
    this->temp_address =
    (this->bus.cpu_read(this->temp_address) |
     (this->bus.cpu_read((this->temp_address + 1) & 0xFF) << 8));

    this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_indirect_y() {
	const uint8_t zero_page_pointer_address = this->bus.cpu_read(this->PC++);

	const uint8_t effective_base_low = this->bus.cpu_read(zero_page_pointer_address);

	const uint8_t wrapped_pointer_high_address = static_cast<uint8_t>(zero_page_pointer_address + 1);
	const uint8_t effective_base_high = this->bus.cpu_read(wrapped_pointer_high_address);

	const uint16_t effective_base_address = static_cast<uint16_t>(effective_base_low) |
											(static_cast<uint16_t>(effective_base_high) << 8);

	this->temp_address = static_cast<uint16_t>(effective_base_address + this->Y);

	this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_zero_page() {
    this->temp_address = this->bus.cpu_read(PC++);
    this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_zero_page_x() {
    this->temp_address = (this->bus.cpu_read(PC) + this->X) & 0xFF;
    this->temp_value = this->bus.cpu_read(this->temp_address);

    this->PC++;
}

void CPU::CPU::addressing_zero_page_y() {
	const std::uint8_t base_address = this->bus.cpu_read(this->PC);
	this->PC++;

	const std::uint8_t wrapped_address = static_cast<std::uint8_t>(base_address + this->Y);

	this->temp_address = static_cast<std::uint16_t>(wrapped_address);

	this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_relative() {
    this->temp_value = this->bus.cpu_read(PC++);
}
