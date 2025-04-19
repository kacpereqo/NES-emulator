//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Branch if Carry Clear
void CPU::CPU::BCC(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Carry) == false)
        this->PC += value + 2;
}

// Branch if Carry Set
void CPU::CPU::BCS(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Carry) == true)
        this->PC += value + 2;
}

// Branch if Equal (Zero flag set)
void CPU::CPU::BEQ(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Zero) == true)
        this->PC += value + 2;
}

// Branch if Minus (Negative flag set)
void CPU::CPU::BMI(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Negative) == true)
        this->PC += value + 2;
}

// Branch if Not Equal (Zero flag clear)
void CPU::CPU::BNE(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Zero) == false)
        this->PC += value + 2;
}

// Branch if Positive (Negative flag clear)
void CPU::CPU::BPL(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Negative) == false)
        this->PC += value + 2;
}

// Branch if Overflow Clear
void CPU::CPU::BVC(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Overflow) == false)
        this->PC += value + 2;
}

// Branch if Overflow Set
void CPU::CPU::BVS(const std::int8_t value) {
    if (this->get_processor_status_flag(ProcessorStatus::Overflow) == true)
        this->PC += value + 2;
}
