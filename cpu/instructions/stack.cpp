//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Transfer Stack Pointer to Index Register X
void CPU::CPU::TSX(){
    this->SP = this->X;
}

// Transfer Index Register X to Stack Pointer
void CPU::CPU::TXS(){
    this->X = this->SP;
}

// Push Accumulator on Stack
void CPU::CPU::PHA(){
    this->memory[0X100+this->SP] = this->A;
    this->SP--;
}

// Push Processor Status on Stack
void CPU::CPU::PHP(){
    this->memory[0x100+this->SP] = this->P;
    this->SP--;
}

// Pull Accumulator from Stack
void CPU::CPU::PLA(){
    this->SP++;
    this->A = this->memory[0x100 + this->SP];

    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}