//
// Created by thinkPaździerż on 18.04.2025.
//
#include "../cpu.h"

// Increment Memory
void CPU::CPU::INC() {
  const std::uint8_t value = this->bus.cpu_read(this->temp_address) + 1;
  this->bus.cpu_write(this->temp_address, value);

  this->set_processor_status_flag(ProcessorStatus::Zero, value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);
}

// Increment Index Register X
void CPU::CPU::INX() {
  this->X++;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->X == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->X & 0x80);
}

// Increment Index Register Y
void CPU::CPU::INY() {
  this->Y++;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->Y & 0x80);
}

// Decrement Memory
void CPU::CPU::DEC() {
  const std::uint8_t value = this->bus.cpu_read(this->temp_address);
  this->bus.cpu_write(this->temp_address, value - 1);

  this->set_processor_status_flag(ProcessorStatus::Zero, value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);
}

// Decrement Index Register X
void CPU::CPU::DEX() {
  this->X--;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->X == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->X & 0x80);
}

// Decrement Index Register Y
void CPU::CPU::DEY() {
  this->Y--;

  this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, this->Y & 0x80);
}
