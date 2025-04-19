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
    this->push_to_stack(this->PC);

    this->PC = address;
}

// Return from Subroutine
void CPU::CPU::RTS() {
    this->PC = this->pop_from_stack<std::uint16_t>();
    this->PC++;
}
