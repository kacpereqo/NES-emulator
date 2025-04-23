//
// Created by thinkPaździerż on 19.04.2025.
//

#include "cpu.h"
#include <iostream>

void CPU::CPU::init() {
    const std::uint8_t reset_vector_low = memory[0xFFFC];
    const std::uint8_t reset_vector_high = memory[0xFFFD];

    this->PC = reset_vector_low | (reset_vector_high << 8);
}

void CPU::CPU::run() {

    const std::uint8_t opcode = memory[PC++];

    static const std::array<Instruction, 256> instruction_set {
        {
            { BRK, addressing_immediate, 7 },
            { ORA, addressing_indirect_x, 6 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 3 },
            { ORA, addressing_zero_page, 3 },
            { ASL, addressing_zero_page, 5 },
            { XXX, addressing_implied, 5 },
            { PHP, addressing_implied, 3 },
            { ORA, addressing_immediate, 2 },
            { ASL, addressing_accumulator, 2 },
            { XXX, addressing_implied, 2 },
            { NOP, addressing_implied, 4 },
            { ORA, addressing_absolute, 4 },
            { ASL, addressing_absolute, 6 },
            { XXX, addressing_implied, 6 },
            { BPL, addressing_relative, 2 },
            { ORA, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 4 },
            { ORA, addressing_zero_page_x, 4 },
            { ASL, addressing_zero_page_x, 6 },
            { XXX, addressing_implied, 6 },
            { CLC, addressing_implied, 2 },
            { ORA, addressing_absolute_y, 4 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 4 },
            { ORA, addressing_absolute_x, 4 },
            { ASL, addressing_absolute_x, 7 },
            { XXX, addressing_implied, 7 },
            { JSR, addressing_absolute, 6 },
            { AND, addressing_indirect_x, 6 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { BIT, addressing_zero_page, 3 },
            { AND, addressing_zero_page, 3 },
            { ROL, addressing_zero_page, 5 },
            { XXX, addressing_implied, 5 },
            { PLP, addressing_implied, 4 },
            { AND, addressing_immediate, 2 },
            { ROL, addressing_accumulator, 2 },
            { XXX, addressing_implied, 2 },
            { BIT, addressing_absolute, 4 },
            { AND, addressing_absolute, 4 },
            { ROL, addressing_absolute, 6 },
            { XXX, addressing_implied, 6 },
            { BMI, addressing_relative, 2 },
            { AND, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 4 },
            { AND, addressing_zero_page_x, 4 },
            { ROL, addressing_zero_page_x, 6 },
            { XXX, addressing_implied, 6 },
            { SEC, addressing_implied, 2 },
            { AND, addressing_absolute_y, 4 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 4 },
            { AND, addressing_absolute_x, 4 },
            { ROL, addressing_absolute_x, 7 },
            { XXX, addressing_implied, 7 },
            { RTI, addressing_implied, 6 },
            { EOR, addressing_indirect_x, 6 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 3 },
            { EOR, addressing_zero_page, 3 },
            { LSR, addressing_zero_page, 5 },
            { XXX, addressing_implied, 5 },
            { PHA, addressing_implied, 3 },
            { EOR, addressing_immediate, 2 },
            { LSR, addressing_accumulator, 2 },
            { XXX, addressing_implied, 2 },
            { JMP, addressing_absolute, 3 },
            { EOR, addressing_absolute, 4 },
            { LSR, addressing_absolute, 6 },
            { XXX, addressing_implied, 6 },
            { BVC, addressing_relative, 2 },
            { EOR, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 4 },
            { EOR, addressing_zero_page_x, 4 },
            { LSR, addressing_zero_page_x, 6 },
            { XXX, addressing_implied, 6 },
            { CLI, addressing_implied, 2 },
            { EOR, addressing_absolute_y, 4 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 4 },
            { EOR, addressing_absolute_x, 4 },
            { LSR, addressing_absolute_x, 7 },
            { XXX, addressing_implied, 7 },
            { RTS, addressing_implied, 6 },
            { ADC, addressing_indirect_x, 6 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 3 },
            { ADC, addressing_zero_page, 3 },
            { ROR, addressing_zero_page, 5 },
            { XXX, addressing_implied, 5 },
            { PLA, addressing_implied, 4 },
            { ADC, addressing_immediate, 2 },
            { ROR, addressing_accumulator, 2 },
            { XXX, addressing_implied, 2 },
            { JMP, addressing_indirect, 5 },
            { ADC, addressing_absolute, 4 },
            { ROR, addressing_absolute, 6 },
            { XXX, addressing_implied, 6 },
            { BVS, addressing_relative, 2 },
            { ADC, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 4 },
            { ADC, addressing_zero_page_x, 4 },
            { ROR, addressing_zero_page_x, 6 },
            { XXX, addressing_implied, 6 },
            { SEI, addressing_implied, 2 },
            { ADC, addressing_absolute_y, 4 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 4 },
            { ADC, addressing_absolute_x, 4 },
            { ROR, addressing_absolute_x, 7 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 2 },
            { STA, addressing_indirect_x, 6 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 6 },
            { STY, addressing_zero_page, 3 },
            { STA, addressing_zero_page, 3 },
            { STX, addressing_zero_page, 3 },
            { XXX, addressing_implied, 3 },
            { DEY, addressing_implied, 2 },
            { NOP, addressing_implied, 2 },
            { TXA, addressing_implied, 2 },
            { XXX, addressing_implied, 2 },
            { STY, addressing_absolute, 4 },
            { STA, addressing_absolute, 4 },
            { STX, addressing_absolute, 4 },
            { XXX, addressing_implied, 4 },
            { BCC, addressing_relative, 2 },
            { STA, addressing_indirect_y, 6 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 6 },
            { STY, addressing_zero_page_x, 4 },
            { STA, addressing_zero_page_x, 4 },
            { STX, addressing_zero_page_y, 4 },
            { XXX, addressing_implied, 4 },
            { TYA, addressing_implied, 2 },
            { STA, addressing_absolute_y, 5 },
            { TXS, addressing_implied, 2 },
            { XXX, addressing_implied, 5 },
            { NOP, addressing_implied, 5 },
            { STA, addressing_absolute_x, 5 },
            { XXX, addressing_implied, 5 },
            { XXX, addressing_implied, 5 },
            { LDY, addressing_immediate, 2 },
            { LDA, addressing_indirect_x, 6 },
            { LDX, addressing_immediate, 2 },
            { XXX, addressing_implied, 6 },
            { LDY, addressing_zero_page, 3 },
            { LDA, addressing_zero_page, 3 },
            { LDX, addressing_zero_page, 3 },
            { XXX, addressing_implied, 3 },
            { TAY, addressing_implied, 2 },
            { LDA, addressing_immediate, 2 },
            { TAX, addressing_implied, 2 },
            { XXX, addressing_implied, 2 },
            { LDY, addressing_absolute, 4 },
            { LDA, addressing_absolute, 4 },
            { LDX, addressing_absolute, 4 },
            { XXX, addressing_implied, 4 },
            { BCS, addressing_relative, 2 },
            { LDA, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 5 },
            { LDY, addressing_zero_page_x, 4 },
            { LDA, addressing_zero_page_x, 4 },
            { LDX, addressing_zero_page_y, 4 },
            { XXX, addressing_implied, 4 },
            { CLV, addressing_implied, 2 },
            { LDA, addressing_absolute_y, 4 },
            { TSX, addressing_implied, 2 },
            { XXX, addressing_implied, 4 },
            { LDY, addressing_absolute_x, 4 },
            { LDA, addressing_absolute_x, 4 },
            { LDX, addressing_absolute_y, 4 },
            { XXX, addressing_implied, 4 },
            { CPY, addressing_immediate, 2 },
            { CMP, addressing_indirect_x, 6 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { CPY, addressing_zero_page, 3 },
            { CMP, addressing_zero_page, 3 },
            { DEC, addressing_zero_page, 5 },
            { XXX, addressing_implied, 5 },
            { INY, addressing_implied, 2 },
            { CMP, addressing_immediate, 2 },
            { DEX, addressing_implied, 2 },
            { XXX, addressing_implied, 2 },
            { CPY, addressing_absolute, 4 },
            { CMP, addressing_absolute, 4 },
            { DEC, addressing_absolute, 6 },
            { XXX, addressing_implied, 6 },
            { BNE, addressing_relative, 2 },
            { CMP, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 4 },
            { CMP, addressing_zero_page_x, 4 },
            { DEC, addressing_zero_page_x, 6 },
            { XXX, addressing_implied, 6 },
            { CLD, addressing_implied, 2 },
            { CMP, addressing_absolute_y, 4 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 4 },
            { CMP, addressing_absolute_x, 4 },
            { DEC, addressing_absolute_x, 7 },
            { XXX, addressing_implied, 7 },
            { CPX, addressing_immediate, 2 },
            { SBC, addressing_indirect_x, 6 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { CPX, addressing_zero_page, 3 },
            { SBC, addressing_zero_page, 3 },
            { INC, addressing_zero_page, 5 },
            { XXX, addressing_implied, 5 },
            { INX, addressing_implied, 2 },
            { SBC, addressing_immediate, 2 },
            { NOP, addressing_implied, 2 },
            { SBC, addressing_implied, 2 },
            { CPX, addressing_absolute, 4 },
            { SBC, addressing_absolute, 4 },
            { INC, addressing_absolute, 6 },
            { XXX, addressing_implied, 6 },
            { BEQ, addressing_relative, 2 },
            { SBC, addressing_indirect_y, 5 },
            { XXX, addressing_implied, 2 },
            { XXX, addressing_implied, 8 },
            { NOP, addressing_implied, 4 },
            { SBC, addressing_zero_page_x, 4 },
            { INC, addressing_zero_page_x, 6 },
            { XXX, addressing_implied, 6 },
            { SED, addressing_implied, 2 },
            { SBC, addressing_absolute_y, 4 },
            { NOP, addressing_implied, 2 },
            { XXX, addressing_implied, 7 },
            { NOP, addressing_implied, 4 },
            { SBC, addressing_absolute_x, 4 },
            { INC, addressing_absolute_x, 7 },
            { XXX, addressing_implied, 7 },
        }
    };
    std::cout << "PC:" << std::hex << static_cast<int>(PC) << " Opcode:" << std::hex << static_cast<int>(opcode) << std::endl;

    const Instruction instruction = instruction_set[opcode];

    (this->*instruction.addressing_mode_handler)();
    (this->*instruction.instruction_handler)();
    this->cpu_cycle_delay = instruction.cycles - 1;
}

void CPU::CPU::addressing_accumulator() {
    this->temp_value = this->A;
}

void CPU::CPU::addressing_absolute() {
    // std::cout << "addressing_absolute" << std::endl;
    this->temp_value = (this->memory[PC] | (this->memory[PC + 1] << 8));
    this->PC += 2;
}

void CPU::CPU::addressing_absolute_x() {
    this->temp_address = (this->memory[PC] | (this->memory[PC + 1] << 8)) + this->X;
    this->temp_value = this->memory[this->temp_address];
    this->PC += 2;
}

void CPU::CPU::addressing_absolute_y() {
    this->temp_address = (this->memory[PC] | (this->memory[PC + 1] << 8)) + this->Y;
    this->temp_value = this->memory[this->temp_address];
    this->PC += 2;
}

void CPU::CPU::addressing_immediate() {
    this->temp_value = this->memory[this->PC++];
}

void CPU::CPU::addressing_implied() {
    ;
}

void CPU::CPU::addressing_indirect() {
    this->temp_value = (this->memory[PC] | (this->memory[PC + 1] << 8));
    this->PC += 2;
    this->temp_value = (this->memory[this->temp_value] | (this->memory[this->temp_value + 1] << 8));
}

void CPU::CPU::addressing_indirect_x() {
    this->temp_address = (this->memory[this->PC++] + this->X) & 0xFF;
    this->temp_address = (this->memory[this->temp_address] | (this->memory[(this->temp_address + 1) & 0xFF] << 8));

    this->temp_value = this->memory[this->temp_address];
}

void CPU::CPU::addressing_indirect_y() {
    this->temp_address = this->memory[PC++];
    this->temp_address = (this->memory[temp_address] | (this->memory[(temp_address + 1) & 0xFF] << 8)) + this->Y;

    this->temp_value = this->memory[this->temp_address];
}

void CPU::CPU::addressing_zero_page() {
    this->temp_address = this->memory[PC++];
    this->temp_value = this->memory[this->temp_address];
}

void CPU::CPU::addressing_zero_page_x() {
    this->temp_address = (this->memory[PC] + this->X) & 0xFF;
    this->temp_value = this->memory[this->temp_address];

    this->PC++;
}

void CPU::CPU::addressing_zero_page_y() {
    this->temp_address = (this->memory[PC] + this->Y) & 0xFF;
    this->temp_value = this->memory[this->temp_address];

    this->PC++;
}

void CPU::CPU::addressing_relative() {
    this->temp_value = this->PC + static_cast<std::int8_t>(this->memory[PC]);
    this->PC++;
}