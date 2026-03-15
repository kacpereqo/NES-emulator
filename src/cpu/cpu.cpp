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
    if (this->cpu_cycle_delay == 0) {

        if (is_nmi_pending) {
            this->is_nmi_pending = false;
            this->nmi_handler();
            this->cpu_cycle_delay = 7;
        }

        else {
            const std::uint8_t opcode = this->bus.cpu_read(PC++);

            const auto [instruction_handler, addressing_mode_handler, cycles] = instruction_set[opcode];

            (this->*addressing_mode_handler)();
            (this->*instruction_handler)();
            this->cpu_cycle_delay = cycles;
        }
    }

    this->cpu_cycle_delay--;
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
    const std::uint8_t low_byte = this->bus.cpu_read(this->PC++);
    const std::uint8_t high_byte = this->bus.cpu_read(this->PC++);
    const std::uint16_t address = (high_byte << 8) | low_byte;

    this->temp_address =
            this->bus.cpu_read(address) | (this->bus.cpu_read(address + 1) << 8);
}

void CPU::CPU::addressing_indirect_x() {
    this->temp_address = (this->bus.cpu_read(this->PC++) + this->X) & 0xFF;
    this->temp_address =
    (this->bus.cpu_read(this->temp_address) |
     (this->bus.cpu_read((this->temp_address + 1) & 0xFF) << 8));

    this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_indirect_y() {
    this->temp_address = this->bus.cpu_read(PC++);
    this->temp_address = (this->bus.cpu_read(temp_address) |
                          (this->bus.cpu_read(temp_address + 1) & 0xFF) << 8) +
                         this->Y;

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
    this->temp_address = this->bus.cpu_read(PC) + this->Y;
    this->temp_value = this->bus.cpu_read(this->temp_address);

    this->PC++;
}

void CPU::CPU::addressing_relative() {
    this->temp_value = this->bus.cpu_read(PC++);
}
