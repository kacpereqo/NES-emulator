//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Arithmetic Shift Left
void CPU::CPU::ASL_accumulator() {
  this->A <<= 1;

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0x80);
  this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative,
                                  this->temp_value & 0x80);
}

void CPU::CPU::ASL() {
  const std::uint8_t result = this->temp_value << 1;
  this->bus.cpu_write(this->temp_address, result);

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0x80);
  this->set_processor_status_flag(ProcessorStatus::Zero, result == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, result & 0x80);
}

void CPU::CPU::LSR_accumulator() {
  const std::uint8_t result = this->temp_value >> 1;
  this->A = result;

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0x01);
  this->set_processor_status_flag(ProcessorStatus::Zero, result == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, result & 0x80);
}

// Logical Shift Right
void CPU::CPU::LSR() {
  const std::uint8_t result = this->temp_value >> 1;
  this->bus.cpu_write(this->temp_address, result);

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0x01);
  this->set_processor_status_flag(ProcessorStatus::Zero, result == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative, result & 0x80);
}

void CPU::CPU::ROL_accumulator() {
  const std::uint8_t result =
      (this->temp_value << 1) |
      this->get_processor_status_flag(ProcessorStatus::Carry);
  this->A = result;

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0b1000'0000);
  this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative,
                                  result & 0b1000'0000);
}

// Rotate Left
void CPU::CPU::ROL() {
  const std::uint8_t result =
      (this->temp_value << 1) |
      this->get_processor_status_flag(ProcessorStatus::Carry);
  this->bus.cpu_write(this->temp_address, result);

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0b1000'0000);
  this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative,
                                  result & 0b1000'0000);
}

void CPU::CPU::ROR_accumulator() {
  const std::uint8_t result =
      (this->temp_value >> 1) |
      this->get_processor_status_flag(ProcessorStatus::Carry);
  this->A = result;

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0b0000'0001);
  this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative,
                                  result & 0b1000'0000);
}

// Rotate Right
void CPU::CPU::ROR() {
  const std::uint8_t result =
      (this->temp_value >> 1) |
      (this->get_processor_status_flag(ProcessorStatus::Carry) << 7);
  this->bus.cpu_write(this->temp_address, result);

  this->set_processor_status_flag(ProcessorStatus::Carry,
                                  this->temp_value & 0b0000'0001);
  this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
  this->set_processor_status_flag(ProcessorStatus::Negative,
                                  result & 0b1000'0000);
}