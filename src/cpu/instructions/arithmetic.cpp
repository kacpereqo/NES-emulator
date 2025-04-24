//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

std::int16_t to_twos_complement(std::int16_t value) {
    if (value & 0x8000) {
        value = -((~value + 1) & 0xFFFF);
    }
    return value;
}

// Add with Carry
void CPU::CPU::ADC(){

    if (this->get_processor_status_flag(ProcessorStatus::DecimalMode)) {
        // TODO:
        // refactor

        uint8_t carry_in = this->get_processor_status_flag(ProcessorStatus::Carry);
        uint8_t a = this->A;
        uint8_t value = this->temp_value;

        uint8_t low_nibble_sum = (a & 0x0F) + (value & 0x0F) + carry_in;

        const std::int16_t temp_sum = to_twos_complement(a>>4) + to_twos_complement(value>>4);

        std::cout << std::hex << "A: " << static_cast<int>(a) << " value: " << static_cast<int>(value) << std::endl;

        uint8_t high_nibble_sum = (a >> 4) + (value >> 4);

        if (low_nibble_sum > 9) {
            low_nibble_sum += 6;
            high_nibble_sum++;
        }

        if (high_nibble_sum > 9) {
            high_nibble_sum += 6;
        }

        uint8_t result = (high_nibble_sum << 4) | (low_nibble_sum & 0x0F);
        this->A = result & 0xFF;

        this->set_processor_status_flag(ProcessorStatus::Carry, high_nibble_sum > 0x0F);
        this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
        this->set_processor_status_flag(ProcessorStatus::Negative, (this->A & 0x10));
        this->set_processor_status_flag(ProcessorStatus::Overflow, temp_sum >= -8  && temp_sum <= 7);

    } else {
        const std::uint16_t temp = this->A + this->temp_value + this->get_processor_status_flag(ProcessorStatus::Carry);
        this->A = temp & 0xFF;

        this->set_processor_status_flag(ProcessorStatus::Carry, temp > 0xFF);
        this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
        this->set_processor_status_flag(ProcessorStatus::Overflow, ((this->A ^ this->temp_value) & (this->A ^ this->A)) & 0x80);
        this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
    }
}

// Subtract with Carry
void CPU::CPU::SBC(){
    this->A += ~this->temp_value + this->get_processor_status_flag(ProcessorStatus::Carry);

    // this->set_processor_status_flag(ProcessorStatus::Carry, this->A  0xFF);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == 0);
    this->set_processor_status_flag(ProcessorStatus::Overflow, ((this->A ^ this->temp_value) & (this->A ^ this->A)) & 0x80);
    this->set_processor_status_flag(ProcessorStatus::Negative, this->A & 0x80);
}

// Compare Accumulator
void CPU::CPU::CMP(){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->A >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->A == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->A - this->temp_value) & 0x80);
}

// Compare Index Register X
void CPU::CPU::CPX(){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->X >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->X == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->X - this->temp_value) & 0x80);
}

// Compare Index Register Y
void CPU::CPU::CPY(){
    this->set_processor_status_flag(ProcessorStatus::Carry, this->Y >= this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Zero, this->Y == this->temp_value);
    this->set_processor_status_flag(ProcessorStatus::Negative, (this->Y - this->temp_value) & 0x80);
}