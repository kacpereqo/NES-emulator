//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Arithmetic Shift Left
void CPU::CPU::ASL() {
    this->temp_value <<= 1;

    this->set_processor_status_flag(ProcessorStatus::Carry, this->temp_value & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->temp_value & 0x80);
}

// Logical Shift Right
void CPU::CPU::LSR() {
    this->temp_value >>= 1;

    this->set_processor_status_flag(ProcessorStatus::Carry, this->temp_value & 0x01);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->temp_value & 0x80);
}

// Rotate Left
void CPU::CPU::ROL() {
    this->temp_value <<= 1;
    this->temp_value = static_cast<std::int8_t>(this->temp_value | (this->get_processor_status_flag(ProcessorStatus::Carry)));

    this->set_processor_status_flag(ProcessorStatus::Carry, this->temp_value & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->temp_value & 0x80);
}

// Rotate Right
void CPU::CPU::ROR() {
    this->temp_value >>= 1;
    this->temp_value = static_cast<std::int8_t>(this->temp_value | (this->get_processor_status_flag(ProcessorStatus::Carry)));

    this->set_processor_status_flag(ProcessorStatus::Carry, this->temp_value & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->temp_value == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->temp_value & 0x80);

}
