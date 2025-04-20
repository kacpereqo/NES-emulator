//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Add with Carry
void CPU::CPU::ADC(){
    this->A += this->temp_value + this->get_processor_status_flag(ProcessorStatus::Carry);

    this->set_processor_status_flag(ProcessorStatus::Carry, this->A > 0xFF);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, ((this->A ^ this->temp_value) & (this->A ^ this->A)) & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Subtract with Carry
void CPU::CPU::SBC(){
    this->A += ~this->temp_value + this->get_processor_status_flag(ProcessorStatus::Carry);

    this->set_processor_status_flag(ProcessorStatus::Carry, this->A > 0xFF);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, ((this->A ^ this->temp_value) & (this->A ^ this->A)) & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Compare Accumulator
void CPU::CPU::CMP(){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->A >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->A - this->temp_value) & 0x80);
}

// Compare Index Register X
void CPU::CPU::CPX(){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->X >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->X == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->X - this->temp_value) & 0x80);
}

// Compare Index Register Y
void CPU::CPU::CPY(){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->Y >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->Y - this->temp_value) & 0x80);
}