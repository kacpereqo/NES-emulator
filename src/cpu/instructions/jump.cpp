//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Jump to this->temp_address
void CPU::CPU::JMP() {
    this->PC = this->temp_address;
}

// Jump to Subroutine
void CPU::CPU::JSR() {
    this->PC -= 1;
    this->push_to_stack(this->PC);

    this->PC = this->temp_address;
}

// Return from Subroutine
void CPU::CPU::RTS() {
    this->PC = this->pop_from_stack<std::uint16_t>();
    this->PC++;
}
