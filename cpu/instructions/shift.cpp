//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Arithmetic Shift Left
void CPU::CPU::ASL(std::int8_t & value) {
    value <<= 1;

    this->set_processor_status_flag(ProcessorStatus::Carry, value & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Zero, value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);
}

// Logical Shift Right
void CPU::CPU::LSR(std::int8_t & value) {
    value >>= 1;

    this->set_processor_status_flag(ProcessorStatus::Carry, value & 0x01);
    this->set_processor_status_flag(ProcessorStatus::Zero, value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);
}

// Rotate Left
void CPU::CPU::ROL(std::int8_t & value) {
    value <<= 1;
    value = static_cast<std::int8_t>(value | (this->get_processor_status_flag(ProcessorStatus::Carry)));

    this->set_processor_status_flag(ProcessorStatus::Carry, value & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Zero, value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);
}

// Rotate Right
void CPU::CPU::ROR(std::int8_t & value) {
    value >>= 1;
    value = static_cast<std::int8_t>(value | (this->get_processor_status_flag(ProcessorStatus::Carry)));

    this->set_processor_status_flag(ProcessorStatus::Carry, value & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Zero, value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, value & 0x80);

}
