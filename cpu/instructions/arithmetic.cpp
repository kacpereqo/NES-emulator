//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Add with Carry
void CPU::CPU::ADC(const std::int8_t value){
    this->A += value + this->get_processor_status_flag(ProcessorStatus::Carry);

    this->set_processor_status_flag(ProcessorStatus::Carry, this->A > 0xFF);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, ((this->A ^ value) & (this->A ^ this->A)) & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Subtract with Carry
void CPU::CPU::SBC(const std::int8_t value){
    this->A += ~value + this->get_processor_status_flag(ProcessorStatus::Carry);

    this->set_processor_status_flag(ProcessorStatus::Carry, this->A > 0xFF);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, ((this->A ^ value) & (this->A ^ this->A)) & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Compare Accumulator
void CPU::CPU::CMP(const std::int8_t value){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->A >= value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->A - value) & 0x80);
}

// Compare Index Register X
void CPU::CPU::CPX(const std::int8_t value){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->X >= value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->X == value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->X - value) & 0x80);
}

// Compare Index Register Y
void CPU::CPU::CPY(std::int8_t value){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->Y >= value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->Y - value) & 0x80);
}