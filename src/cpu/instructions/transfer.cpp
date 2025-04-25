//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Transfer Accumulator to Index Register X
void CPU::CPU::TAX(){
    this->X = this->A;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->X == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->X & 0x80) != 0);
}

// Transfer Accumulator to Index Register Y
void CPU::CPU::TAY(){
    this->Y = this->A;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->Y & 0x80) != 0);
}

// Transfer Stack Pointer to Index Register X
void CPU::CPU::TXA(){
    this->A = this->X;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->A & 0x80) != 0);
}

// Transfer Index Register X to Accumulator
void CPU::CPU::TYA(){
    this->A = this->Y;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->A & 0x80) != 0);
}