//
// Created by thinkPaździerż on 18.04.2025.
//
#include "../cpu.h"

 // Increment Memory
void CPU::CPU::INC(const std::int16_t address) {
    this->memory[address]++;
}

 // Increment Index Register X
void CPU::CPU::INX() {
    this->X++;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->X == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->X & 0x80);
}

 // Increment Index Register Y
void CPU::CPU::INY() {
    this->Y++;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->Y & 0x80);
}

 // Decrement Memory
void CPU::CPU::DEC(std::int16_t address) {
    this->memory[address]--;
}

 // Decrement Index Register X
void CPU::CPU::DEX() {
    this->X--;
}

 // Decrement Index Register Y
void CPU::CPU::DEY() {
    this->Y--;
}
