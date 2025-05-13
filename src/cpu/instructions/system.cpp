//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Force Break
void CPU::CPU::BRK() {
  this->set_processor_status_flag(ProcessorStatus::BreakCommand, true);

  this->push_to_stack(this->PC);
  this->push_to_stack(this->P);

  // this->PC = this->bus.cpu_read(0xFFFE) | (this->bus.cpu_read(0xFFFF) << 8);
  // this->PC = (this->memory[0xFFFF] << 8) | this->memory[0xFFFF - 1];
  this->PC = this->bus.cpu_read(0xFFFF) << 8;
  this->PC |= this->bus.cpu_read(0xFFFE);

  this->set_processor_status_flag(ProcessorStatus::BreakCommand, false);
  this->set_processor_status_flag(ProcessorStatus::InterruptDisable, true);
}

// No Operation
void CPU::CPU::NOP() { ; }

// Stop Execution (Return from Interrupt)
void CPU::CPU::RTI() {
  this->P = this->pop_from_stack<std::uint8_t>();

  this->set_processor_status_flag(ProcessorStatus::InterruptDisable, true);
  this->set_processor_status_flag(ProcessorStatus::BreakCommand, false);
  this->set_processor_status_flag(ProcessorStatus::Unused, true);

  this->PC = this->pop_from_stack<std::uint16_t>();
}
