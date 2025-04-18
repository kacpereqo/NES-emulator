//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Load Accumulator
void CPU::CPU::LDA(const std::uint8_t value) {
    this->A = value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Load Index Register X
void CPU::CPU::LDX(const std::uint8_t value) {
    this->X = value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Load Index Register Y
void CPU::CPU::LDY(const std::uint8_t value) {
    this->Y = value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Store Accumulator
void CPU::CPU::STA(const std::uint16_t address) {
    this->memory[address] = this->A;
}

// Store Index Register X
void CPU::CPU::STX(const std::uint16_t address) {
    this->memory[address] = this->X;
}

// Store Index Register Y
void CPU::CPU::STY(const std::uint16_t address) {
    this->memory[address] = this->Y;
}