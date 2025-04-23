//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Logical AND
void CPU::CPU::AND(){
    std::cout << "AND" << " " << std::hex << static_cast<int>(this->temp_value) << std::endl;
    this->A &= this->temp_value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Logical OR
void CPU::CPU::ORA() {
    this->A |= this->temp_value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Logical XOR
void CPU::CPU::EOR(){
    this->A ^= this->temp_value;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Bit Test
void CPU::CPU::BIT(){
    this->set_processor_status_flag(ProcessorStatus::Zero, (this->A & this->temp_value) == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, this->temp_value & 0x40);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->temp_value & 0x80);
}
