//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Load Accumulator
void CPU::CPU::LDA() {
  this->A = this->temp_value;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Load Index Register X
void CPU::CPU::LDX() {
  this->X = this->temp_value;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->X == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->X & 0x80);
}

// Load Index Register Y
void CPU::CPU::LDY() {
  this->Y = this->temp_value;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->Y & 0x80);
}

// Store Accumulator
void CPU::CPU::STA() { this->bus.cpu_write(this->temp_address, this->A); }

// Store Index Register X
void CPU::CPU::STX() { this->bus.cpu_write(this->temp_address, this->X); }

// Store Index Register Y
void CPU::CPU::STY() { this->bus.cpu_write(this->temp_address, this->Y); }