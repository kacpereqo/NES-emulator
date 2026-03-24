//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"
#include <cassert>

std::int16_t to_twos_complement(std::int16_t value) {
    if (value & 0x8000) {
        value = -((~value + 1) & 0xFFFF);
    }
    return value;
}

// Add with Carry
void CPU::CPU::ADC() {
    // 1. Calculate the 16-bit result
    const std::uint16_t result =
            this->A + this->temp_value +
            this->get_processor_status_flag(ProcessorStatus::Carry);

    bool overflow = ((this->A ^ result) & (this->temp_value ^ result) & 0x80) != 0;

    this->A = result & 0xFF;

    this->set_processor_status_flag(ProcessorStatus::Carry, result > 0xFF);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, overflow);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Subtract with Carry
void CPU::CPU::SBC() {
    if (this->get_processor_status_flag(ProcessorStatus::DecimalMode)) return;

    // A = A - memory - ~C
    const std::uint8_t temp_A = this->A;
    const auto result = static_cast<std::int16_t>(
        this->A - this->temp_value -
        !this->get_processor_status_flag(ProcessorStatus::Carry));
    this->A = result & 0xFF;

    this->set_processor_status_flag(ProcessorStatus::Carry, result >= 0x00);
    this->set_processor_status_flag(ProcessorStatus::Zero, result == 0);
    this->set_processor_status_flag(
        ProcessorStatus::Overflow,
        ((temp_A ^ this->temp_value) & (temp_A ^ result) & 0x80) != 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, result & 0x80);
}

// Compare Accumulator
void CPU::CPU::CMP() {
    this->set_processor_status_flag(ProcessorStatus::Carry,
                                    this->A >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero,
                                    this->A == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative,
                                    (this->A - this->temp_value) & 0x80);
}

// Compare Index Register X
void CPU::CPU::CPX() {
    this->set_processor_status_flag(ProcessorStatus::Carry,
                                    this->X >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero,
                                    this->X == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative,
                                    (this->X - this->temp_value) & 0x80);
}

// Compare Index Register Y
void CPU::CPU::CPY() {
    this->set_processor_status_flag(ProcessorStatus::Carry,
                                    this->Y >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero,
                                    this->Y == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative,
                                    (this->Y - this->temp_value) & 0x80);
}