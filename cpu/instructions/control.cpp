//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Clear Carry Flag
void CPU::CPU::CLC() {
    this->set_processor_status_flag(ProcessorStatus::Carry, false);
}

// Clear Decimal Mode
void CPU::CPU::CLD() {
    this->set_processor_status_flag(ProcessorStatus::DecimalMode, false);
}

// Clear Interrupt Disable
void CPU::CPU::CLI() {
    this->set_processor_status_flag(ProcessorStatus::InterruptDisable, false);
}

// Clear Overflow Flag
void CPU::CPU::CLV() {
    this->set_processor_status_flag(ProcessorStatus::Overflow, false);
}

// Set Carry Flag
void CPU::CPU::SEC() {
    this->set_processor_status_flag(ProcessorStatus::Carry, true);
}

// Set Decimal Mode
void CPU::CPU::SED() {
    this->set_processor_status_flag(ProcessorStatus::DecimalMode, true);
}

// Set Interrupt Disable
void CPU::CPU::SEI() {
    this->set_processor_status_flag(ProcessorStatus::InterruptDisable, true);
}
