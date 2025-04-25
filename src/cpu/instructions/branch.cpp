//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Branch if Carry Clear
void CPU::CPU::BCC() {
    if (this->get_processor_status_flag(ProcessorStatus::Carry) == false)
        this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Carry Set
void CPU::CPU::BCS() {
    if (this->get_processor_status_flag(ProcessorStatus::Carry) == true)
        this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Equal (Zero flag set)
void CPU::CPU::BEQ() {
    if (this->get_processor_status_flag(ProcessorStatus::Zero) == true)
        this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Minus (Negative flag set)
void CPU::CPU::BMI() {
    if (this->get_processor_status_flag(ProcessorStatus::Negative) == true)
        this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Not Equal (Zero flag clear)
void CPU::CPU::BNE() {
    if (this->get_processor_status_flag(ProcessorStatus::Zero) == false)
         this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Positive (Negative flag clear)
void CPU::CPU::BPL() {
    if (this->get_processor_status_flag(ProcessorStatus::Negative) == false)
         this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Overflow Clear
void CPU::CPU::BVC() {
    if (this->get_processor_status_flag(ProcessorStatus::Overflow) == false)
         this->PC += static_cast<std::int8_t>(this->temp_value);
}

// Branch if Overflow Set
void CPU::CPU::BVS() {
    if (this->get_processor_status_flag(ProcessorStatus::Overflow) == true)
         this->PC += static_cast<std::int8_t>(this->temp_value);
}
