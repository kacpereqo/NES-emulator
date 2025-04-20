//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Branch if Carry Clear
void CPU::CPU::BCC() {
    if (this->get_processor_status_flag(ProcessorStatus::Carry) == false)
        this->PC += this->temp_address + 2;
}

// Branch if Carry Set
void CPU::CPU::BCS() {
    if (this->get_processor_status_flag(ProcessorStatus::Carry) == true)
        this->PC += this->temp_address + 2;
}

// Branch if Equal (Zero flag set)
void CPU::CPU::BEQ() {
    if (this->get_processor_status_flag(ProcessorStatus::Zero) == true)
        this->PC += this->temp_address + 2;
}

// Branch if Minus (Negative flag set)
void CPU::CPU::BMI() {
    if (this->get_processor_status_flag(ProcessorStatus::Negative) == true)
        this->PC += this->temp_address + 2;
}

// Branch if Not Equal (Zero flag clear)
void CPU::CPU::BNE() {
    if (this->get_processor_status_flag(ProcessorStatus::Zero) == false)
        this->PC += this->temp_address + 2;
}

// Branch if Positive (Negative flag clear)
void CPU::CPU::BPL() {
    if (this->get_processor_status_flag(ProcessorStatus::Negative) == false)
        this->PC += this->temp_address + 2;
}

// Branch if Overflow Clear
void CPU::CPU::BVC() {
    if (this->get_processor_status_flag(ProcessorStatus::Overflow) == false)
        this->PC += this->temp_address + 2;
}

// Branch if Overflow Set
void CPU::CPU::BVS() {
    if (this->get_processor_status_flag(ProcessorStatus::Overflow) == true)
        this->PC += this->temp_address + 2;
}
