//
// Created by thinkPaździerż on 19.04.2025.
//

#include "cpu.h"

void CPU::CPU::set_processor_status_flag(const std::uint8_t flag, const bool value) {
    if (value) {
        P |= flag;
    } else {
        P &= ~flag;
    }
}

bool CPU::CPU::get_processor_status_flag(const std::uint8_t flag) const {
    return P & flag;
}

void CPU::CPU::push_to_stack(const std::uint8_t value) {
    this->memory[0x100 + SP] = value;
    this->SP--;
}

void CPU::CPU::push_to_stack(const std::uint16_t value) {
    this->memory[0x100 + SP] = (value >> 8) & 0xFF; // Push high byte
    this->SP--;

    this->memory[0x100 + SP] = value & 0xFF;        // Push low byte
    this->SP--;
}

template<>
std::uint16_t CPU::CPU::pop_from_stack<std::uint16_t>() {
    SP++;
    const std::uint8_t low_byte = memory[0x100 + SP];

    SP++;
    const std::uint8_t high_byte = memory[0x100 + SP];
    return (high_byte << 8) | low_byte;
}

template<>
std::uint8_t CPU::CPU::pop_from_stack<std::uint8_t>() {
    SP++;
    return memory[0x100 + SP];
}