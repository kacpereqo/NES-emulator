//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Transfer Accumulator to Index Register X
void CPU::CPU::TAX(){
    this->X = this->A;
}

// Transfer Accumulator to Index Register Y
void CPU::CPU::TAY(){
    this->Y = this->A;
}

// Transfer Stack Pointer to Index Register X
void CPU::CPU::TXA(){
    this->A = this->X;
}

// Transfer Index Register X to Accumulator
void CPU::CPU::TYA(){
    this->A = this->Y;
}