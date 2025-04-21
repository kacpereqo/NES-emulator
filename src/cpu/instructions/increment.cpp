//
// Created by thinkPaździerż on 18.04.2025.
//
#include "../cpu.h"

 // Increment Memory
void CPU::CPU::INC() {
    std::cout << "INC" << " " << std::hex << static_cast<int>(this->temp_value) << std::endl;
    this->memory[this->temp_value]++;

    this->set_processor_status_flag(ProcessorStatus::Zero, this->memory[this->temp_value] == 0);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->memory[this->temp_value] & 0x80);
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
    this->memory[this->temp_value]--;
}

 // Decrement Index Register X
void CPU::CPU::DEX() {
    this->X--;
}

 // Decrement Index Register Y
void CPU::CPU::DEY() {
    this->Y--;
}
