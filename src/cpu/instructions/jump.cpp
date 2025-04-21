//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Jump to this->temp_address
void CPU::CPU::JMP() {
    this->PC = this->temp_value;
}

// Jump to Subroutine
void CPU::CPU::JSR() {
    this->push_to_stack(this->PC);

    this->PC = this->temp_value;
}

// Return from Subroutine
void CPU::CPU::RTS() {
    this->PC = this->pop_from_stack<std::uint16_t>();
    this->PC++;
}
