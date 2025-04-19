//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Logical AND
void CPU::CPU::AND(const std::int8_t value){
    this->A &= value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Logical OR
void CPU::CPU::ORA(const std::int8_t value) {
    this->A |= value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Logical XOR
void CPU::CPU::EOR(const std::int8_t value){
    this->A ^= value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Bit Test
void CPU::CPU::BIT(const std::int8_t value){
    this->set_processor_status_flag(ProcessorStatus::Zero, (this->A & value) == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, value & 0x40);
    this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);
}
