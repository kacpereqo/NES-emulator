//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Jump to Address
void CPU::CPU::JMP(const std::uint16_t address) {
    this->PC = address;
}

// Jump to Subroutine
void CPU::CPU::JSR(const std::uint16_t address) {
    this->memory[0x100 + this->SP] = (this->PC >> 8) & 0xFF; // Push high byte
    this->SP--;

    this->memory[0x100 + this->SP] = this->PC & 0xFF;        // Push low byte
    this->SP--;

    this->PC = address;
}

// Return from Subroutine
void CPU::CPU::RTS() {
    this->SP++;
    const std::uint8_t low_byte = this->memory[0x100 + this->SP];
    this->SP++;
    const std::uint8_t high_byte = this->memory[0x100 + this->SP];

    this->PC = (high_byte << 8) | low_byte;
    this->PC++;
}
