//
// Created by thinkPaździerż on 19.04.2025.
//

#include "cpu.h"
#include <iostream>

void CPU::CPU::init() {
  const std::uint8_t reset_vector_low = this->bus.cpu_read(0xFFFC);
  const std::uint8_t reset_vector_high = this->bus.cpu_read(0xFFFD);

  this->PC = reset_vector_low | (reset_vector_high << 8);
}

void CPU::CPU::run() {

  const std::uint8_t opcode = this->bus.cpu_read(PC++);

  static const std::array<Instruction, 256> instruction_set{{
      {&CPU::BRK, &CPU::addressing_immediate, 7},
      {&CPU::ORA, &CPU::addressing_indirect_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 3},
      {&CPU::ORA, &CPU::addressing_zero_page, 3},
      {&CPU::ASL, &CPU::addressing_zero_page, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::PHP, &CPU::addressing_implied, 3},
      {&CPU::ORA, &CPU::addressing_immediate, 2},
      {&CPU::ASL_accumulator, &CPU::addressing_accumulator, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::ORA, &CPU::addressing_absolute, 4},
      {&CPU::ASL, &CPU::addressing_absolute, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::BPL, &CPU::addressing_relative, 2},
      {&CPU::ORA, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::ORA, &CPU::addressing_zero_page_x, 4},
      {&CPU::ASL, &CPU::addressing_zero_page_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::CLC, &CPU::addressing_implied, 2},
      {&CPU::ORA, &CPU::addressing_absolute_y, 4},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::ORA, &CPU::addressing_absolute_x, 4},
      {&CPU::ASL, &CPU::addressing_absolute_x, 7},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::JSR, &CPU::addressing_absolute, 6},
      {&CPU::AND, &CPU::addressing_indirect_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::BIT, &CPU::addressing_zero_page, 3},
      {&CPU::AND, &CPU::addressing_zero_page, 3},
      {&CPU::ROL, &CPU::addressing_zero_page, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::PLP, &CPU::addressing_implied, 4},
      {&CPU::AND, &CPU::addressing_immediate, 2},
      {&CPU::ROL_accumulator, &CPU::addressing_accumulator, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::BIT, &CPU::addressing_absolute, 4},
      {&CPU::AND, &CPU::addressing_absolute, 4},
      {&CPU::ROL, &CPU::addressing_absolute, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::BMI, &CPU::addressing_relative, 2},
      {&CPU::AND, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::AND, &CPU::addressing_zero_page_x, 4},
      {&CPU::ROL, &CPU::addressing_zero_page_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::SEC, &CPU::addressing_implied, 2},
      {&CPU::AND, &CPU::addressing_absolute_y, 4},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::AND, &CPU::addressing_absolute_x, 4},
      {&CPU::ROL, &CPU::addressing_absolute_x, 7},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::RTI, &CPU::addressing_implied, 6},
      {&CPU::EOR, &CPU::addressing_indirect_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 3},
      {&CPU::EOR, &CPU::addressing_zero_page, 3},
      {&CPU::LSR, &CPU::addressing_zero_page, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::PHA, &CPU::addressing_implied, 3},
      {&CPU::EOR, &CPU::addressing_immediate, 2},
      {&CPU::LSR_accumulator, &CPU::addressing_accumulator, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::JMP, &CPU::addressing_absolute, 3},
      {&CPU::EOR, &CPU::addressing_absolute, 4},
      {&CPU::LSR, &CPU::addressing_absolute, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::BVC, &CPU::addressing_relative, 2},
      {&CPU::EOR, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::EOR, &CPU::addressing_zero_page_x, 4},
      {&CPU::LSR, &CPU::addressing_zero_page_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::CLI, &CPU::addressing_implied, 2},
      {&CPU::EOR, &CPU::addressing_absolute_y, 4},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::EOR, &CPU::addressing_absolute_x, 4},
      {&CPU::LSR, &CPU::addressing_absolute_x, 7},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::RTS, &CPU::addressing_implied, 6},
      {&CPU::ADC, &CPU::addressing_indirect_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 3},
      {&CPU::ADC, &CPU::addressing_zero_page, 3},
      {&CPU::ROR, &CPU::addressing_zero_page, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::PLA, &CPU::addressing_implied, 4},
      {&CPU::ADC, &CPU::addressing_immediate, 2},
      {&CPU::ROR_accumulator, &CPU::addressing_accumulator, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::JMP, &CPU::addressing_indirect, 5},
      {&CPU::ADC, &CPU::addressing_absolute, 4},
      {&CPU::ROR, &CPU::addressing_absolute, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::BVS, &CPU::addressing_relative, 2},
      {&CPU::ADC, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::ADC, &CPU::addressing_zero_page_x, 4},
      {&CPU::ROR, &CPU::addressing_zero_page_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::SEI, &CPU::addressing_implied, 2},
      {&CPU::ADC, &CPU::addressing_absolute_y, 4},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::ADC, &CPU::addressing_absolute_x, 4},
      {&CPU::ROR, &CPU::addressing_absolute_x, 7},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::STA, &CPU::addressing_indirect_x, 6},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::STY, &CPU::addressing_zero_page, 3},
      {&CPU::STA, &CPU::addressing_zero_page, 3},
      {&CPU::STX, &CPU::addressing_zero_page, 3},
      {&CPU::XXX, &CPU::addressing_implied, 3},
      {&CPU::DEY, &CPU::addressing_implied, 2},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::TXA, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::STY, &CPU::addressing_absolute, 4},
      {&CPU::STA, &CPU::addressing_absolute, 4},
      {&CPU::STX, &CPU::addressing_absolute, 4},
      {&CPU::XXX, &CPU::addressing_implied, 4},
      {&CPU::BCC, &CPU::addressing_relative, 2},
      {&CPU::STA, &CPU::addressing_indirect_y, 6},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::STY, &CPU::addressing_zero_page_x, 4},
      {&CPU::STA, &CPU::addressing_zero_page_x, 4},
      {&CPU::STX, &CPU::addressing_zero_page_y, 4},
      {&CPU::XXX, &CPU::addressing_implied, 4},
      {&CPU::TYA, &CPU::addressing_implied, 2},
      {&CPU::STA, &CPU::addressing_absolute_y, 5},
      {&CPU::TXS, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::NOP, &CPU::addressing_implied, 5},
      {&CPU::STA, &CPU::addressing_absolute_x, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::LDY, &CPU::addressing_immediate, 2},
      {&CPU::LDA, &CPU::addressing_indirect_x, 6},
      {&CPU::LDX, &CPU::addressing_immediate, 2},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::LDY, &CPU::addressing_zero_page, 3},
      {&CPU::LDA, &CPU::addressing_zero_page, 3},
      {&CPU::LDX, &CPU::addressing_zero_page, 3},
      {&CPU::XXX, &CPU::addressing_implied, 3},
      {&CPU::TAY, &CPU::addressing_implied, 2},
      {&CPU::LDA, &CPU::addressing_immediate, 2},
      {&CPU::TAX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::LDY, &CPU::addressing_absolute, 4},
      {&CPU::LDA, &CPU::addressing_absolute, 4},
      {&CPU::LDX, &CPU::addressing_absolute, 4},
      {&CPU::XXX, &CPU::addressing_implied, 4},
      {&CPU::BCS, &CPU::addressing_relative, 2},
      {&CPU::LDA, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::LDY, &CPU::addressing_zero_page_x, 4},
      {&CPU::LDA, &CPU::addressing_zero_page_x, 4},
      {&CPU::LDX, &CPU::addressing_zero_page_y, 4},
      {&CPU::XXX, &CPU::addressing_implied, 4},
      {&CPU::CLV, &CPU::addressing_implied, 2},
      {&CPU::LDA, &CPU::addressing_absolute_y, 4},
      {&CPU::TSX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 4},
      {&CPU::LDY, &CPU::addressing_absolute_x, 4},
      {&CPU::LDA, &CPU::addressing_absolute_x, 4},
      {&CPU::LDX, &CPU::addressing_absolute_y, 4},
      {&CPU::XXX, &CPU::addressing_implied, 4},
      {&CPU::CPY, &CPU::addressing_immediate, 2},
      {&CPU::CMP, &CPU::addressing_indirect_x, 6},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::CPY, &CPU::addressing_zero_page, 3},
      {&CPU::CMP, &CPU::addressing_zero_page, 3},
      {&CPU::DEC, &CPU::addressing_zero_page, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::INY, &CPU::addressing_implied, 2},
      {&CPU::CMP, &CPU::addressing_immediate, 2},
      {&CPU::DEX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::CPY, &CPU::addressing_absolute, 4},
      {&CPU::CMP, &CPU::addressing_absolute, 4},
      {&CPU::DEC, &CPU::addressing_absolute, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::BNE, &CPU::addressing_relative, 2},
      {&CPU::CMP, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::CMP, &CPU::addressing_zero_page_x, 4},
      {&CPU::DEC, &CPU::addressing_zero_page_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::CLD, &CPU::addressing_implied, 2},
      {&CPU::CMP, &CPU::addressing_absolute_y, 4},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::CMP, &CPU::addressing_absolute_x, 4},
      {&CPU::DEC, &CPU::addressing_absolute_x, 7},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::CPX, &CPU::addressing_immediate, 2},
      {&CPU::SBC, &CPU::addressing_indirect_x, 6},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::CPX, &CPU::addressing_zero_page, 3},
      {&CPU::SBC, &CPU::addressing_zero_page, 3},
      {&CPU::INC, &CPU::addressing_zero_page, 5},
      {&CPU::XXX, &CPU::addressing_implied, 5},
      {&CPU::INX, &CPU::addressing_implied, 2},
      {&CPU::SBC, &CPU::addressing_immediate, 2},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::SBC, &CPU::addressing_implied, 2},
      {&CPU::CPX, &CPU::addressing_absolute, 4},
      {&CPU::SBC, &CPU::addressing_absolute, 4},
      {&CPU::INC, &CPU::addressing_absolute, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::BEQ, &CPU::addressing_relative, 2},
      {&CPU::SBC, &CPU::addressing_indirect_y, 5},
      {&CPU::XXX, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 8},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::SBC, &CPU::addressing_zero_page_x, 4},
      {&CPU::INC, &CPU::addressing_zero_page_x, 6},
      {&CPU::XXX, &CPU::addressing_implied, 6},
      {&CPU::SED, &CPU::addressing_implied, 2},
      {&CPU::SBC, &CPU::addressing_absolute_y, 4},
      {&CPU::NOP, &CPU::addressing_implied, 2},
      {&CPU::XXX, &CPU::addressing_implied, 7},
      {&CPU::NOP, &CPU::addressing_implied, 4},
      {&CPU::SBC, &CPU::addressing_absolute_x, 4},
      {&CPU::INC, &CPU::addressing_absolute_x, 7},
      {&CPU::XXX, &CPU::addressing_implied, 7},
  }};

  const Instruction instruction = instruction_set[opcode];

  (this->*instruction.addressing_mode_handler)();
  (this->*instruction.instruction_handler)();
  this->cpu_cycle_delay = instruction.cycles;

  this->cpu_cycle_delay--;
}

void CPU::CPU::addressing_accumulator() { this->temp_value = this->A; }

void CPU::CPU::addressing_absolute() {
  this->temp_address =
      this->bus.cpu_read(this->PC) | (this->bus.cpu_read(this->PC + 1) << 8);
  this->temp_value = this->bus.cpu_read(this->temp_address);
  this->PC += 2;
}

void CPU::CPU::addressing_absolute_x() {
  this->temp_address =
      (this->bus.cpu_read(this->PC) | (this->bus.cpu_read(this->PC + 1) << 8)) +
      this->X;
  this->temp_value = this->bus.cpu_read(this->temp_address);
  this->PC += 2;
}

void CPU::CPU::addressing_absolute_y() {
  this->temp_address =
      (this->bus.cpu_read(this->PC) | (this->bus.cpu_read(this->PC + 1) << 8)) +
      this->Y;
  this->temp_value = this->bus.cpu_read(this->temp_address);
  this->PC += 2;
}

void CPU::CPU::addressing_immediate() {
  this->temp_value = this->bus.cpu_read(this->PC++);
}

void CPU::CPU::addressing_implied() { ; }

void CPU::CPU::addressing_indirect() {
  const std::uint8_t low_byte = this->bus.cpu_read(this->PC++);
  const std::uint8_t high_byte = this->bus.cpu_read(this->PC++);
  const std::uint16_t address = (high_byte << 8) | low_byte;

  this->temp_address =
      this->bus.cpu_read(address) | (this->bus.cpu_read(address + 1) << 8);
}

void CPU::CPU::addressing_indirect_x() {
  this->temp_address = (this->bus.cpu_read(this->PC++) + this->X) & 0xFF;
  this->temp_address =
      (this->bus.cpu_read(this->temp_address) |
       (this->bus.cpu_read((this->temp_address + 1) & 0xFF) << 8));

  this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_indirect_y() {
  this->temp_address = this->bus.cpu_read(PC++);
  this->temp_address = (this->bus.cpu_read(temp_address) |
                        (this->bus.cpu_read(temp_address + 1) & 0xFF) << 8) +
                       this->Y;

  this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_zero_page() {
  this->temp_address = this->bus.cpu_read(PC++);
  this->temp_value = this->bus.cpu_read(this->temp_address);
}

void CPU::CPU::addressing_zero_page_x() {
  this->temp_address = (this->bus.cpu_read(PC) + this->X) & 0xFF;
  this->temp_value = this->bus.cpu_read(this->temp_address);

  this->PC++;
}

void CPU::CPU::addressing_zero_page_y() {
  this->temp_address = this->bus.cpu_read(PC) + this->Y;
  this->temp_value = this->bus.cpu_read(this->temp_address);

  this->PC++;
}

void CPU::CPU::addressing_relative() {
  this->temp_value = this->bus.cpu_read(PC++);
}