//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Transfer Stack Pointer to Index Register X
void CPU::CPU::TSX(){
    this->X = this->SP;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->SP == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->SP & 0x80);
}

// Transfer Index Register X to Stack Pointer
void CPU::CPU::TXS(){
    this->SP = this->X;
}

// Push Accumulator on Stack
void CPU::CPU::PHA(){
    this->push_to_stack(this->A);
}
`
// Push Processor Status on Stack
void CPU::CPU::PHP(){
    const std::uint8_t temp_P = this->P | ProcessorStatus::BreakCommand;

    this->push_to_stack(temp_P);
}

// Pull Accumulator from Stack
void CPU::CPU::PLA(){
    this->A = this->pop_from_stack<std::uint8_t>();

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Pull Processor Status from Stack
void CPU::CPU::PLP(){
    this->P = this->pop_from_stack<std::uint8_t>();
    this->set_processor_status_flag(ProcessorStatus::BreakCommand, false);
    this->set_processor_status_flag(ProcessorStatus::Unused, true);
}