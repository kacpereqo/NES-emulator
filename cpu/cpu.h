//
// Created by thinkPaździerż on 18.04.2025.
//

#include <cstdint>
#include <array>

#ifndef CPU_H
#define CPU_H


/// Memory secotr
/// Internal RAM ($0000-$07FF)
/// cartridge RAM (usually $6000–$7FFF)
///

namespace CPU {

    namespace ProcessorStatus{
        enum  ProcessorStatus : std::uint8_t {
            Carry            = 1 << 0,
            Zero             = 1 << 1,
            InterruptDisable = 1 << 2,
            DecimalMode      = 1 << 3,
            BreakCommand     = 1 << 4,
            Unused           = 1 << 5,  // 7th bit is unused
            Overflow         = 1 << 6,
            Negative         = 1 << 7,
        };
    }

static constexpr std::uint8_t STACK_START = 0xFD; // Stack starts at 0x0100
static constexpr std::uint16_t PROGRAM_COUNTER = 0xFFFC;
static constexpr std::uint8_t DEFAULT_STATUS =  ProcessorStatus::Unused | ProcessorStatus::InterruptDisable | ProcessorStatus::DecimalMode;


class CPU {
    /// Registers
    /// https://www.nesdev.org/obelisk-6502-guide/registers.html

    std::uint16_t PC; // Program Counter
    std::uint8_t SP;  // Stack Pointer
    std::uint8_t A;   // Accumulator
    std::uint8_t X;   // Index Register X
    std::uint8_t Y;   // Index Register Y

    std::array<std::uint8_t, 0xFFFF> memory;

    std::uint8_t P;   // Processor Status

    // 7  bit  0
    // ---- ----
    // NV1B DIZC
    // |||| ||||
    // |||| |||+- Carry
    // |||| ||+-- Zero
    // |||| |+--- Interrupt Disable
    // |||| +---- Decimal
    // |||+------ (No CPU effect; see: the B flag)
    // ||+------- (No CPU effect; always pushed as 1)
    // |+-------- Overflow
    // +--------- Negative

    /// Constructor

    CPU() : PC(PROGRAM_COUNTER), SP(STACK_START), A(0), X(0), Y(0), P(DEFAULT_STATUS) {}

    /// Instructions

    /// Load/Store
    void LDA(std::uint8_t value);    // Load Accumulator
    void LDX(std::uint8_t value);    // Load Index Register X
    void LDY(std::uint8_t value);    // Load Index Register Y
    void STA(std::uint16_t address); // Store Accumulator
    void STX(std::uint16_t address); // Store Index Register X
    void STY(std::uint16_t address); // Store Index Register Y

    ///Register Transfer
    void TAX(); // Transfer Accumulator to Index Register X
    void TAY(); // Transfer Accumulator to Index Register Y
    void TXA(); // Transfer Stack Pointer to Index Register X
    void TYA(); // Transfer Index Register X to Accumulator

    /// Stack Operations
    void TS`X(); // Transfer Stack Pointer to Index Register X
    void TXS(); // Transfer Index Register X to Stack Pointer
    void PHA(); // Push Accumulator on Stack
    void PHP(); // Push Processor Status on Stack
    void PLA(); // Pull Accumulator from Stack

    /// Logical
    void AND(std::int8_t value); // Logical AND
    void ORA(std::int8_t value); // Logical OR
    void EOR(std::int8_t value); // Logical XOR
    void BIT(std::int8_t value); // Bit Test

    /// Arithmetic
    void ADC(std::int8_t value); // Add with Carry
    void SBC(std::int8_t value); // Subtract with Carry
    void CMP(std::int8_t value); // Compare Accumulator
    void CPX(std::int8_t value); // Compare Index Register X
    void CPY(std::int8_t value); // Compare Index Register Y

    /// Increments & Decrements
    void INC(std::int16_t address); // Increment Memory
    void INX();                     // Increment Index Register X
    void INY();                     // Increment Index Register Y
    void DEC(std::int16_t address); // Decrement Memory
    void DEX();                     // Decrement Index Register X
    void DEY();                     // Decrement Index Register Y

    /// Shifts
    void ASL(std::int8_t value); // Arithmetic Shift Left
    void LSR(std::int8_t value); // Logical Shift Right
    void ROL(std::int8_t value); // Rotate Left
    void ROR(std::int8_t value); // Rotate Right

    /// Jumps & Calls
    void JMP(std::uint16_t address); // Jump to Address
    void JSR(std::uint16_t address); // Jump to Subroutine
    void RTS(); // Return from Subroutine

    /// Branches
    void BCC(std::int8_t value); // Branch if Equal
    void BCS(std::int8_t value); // Branch if Carry Set
    void BEQ(std::int8_t value); // Branch if Equal
    void BMI(std::int8_t value); // Branch if Minus
    void BNE(std::int8_t value); // Branch if Not Equal
    void BPL(std::int8_t value); // Branch if Positive
    void BVC(std::int8_t value); // Branch if Overflow Clear
    void BVS(std::int8_t value); // Branch if Overflow Set

    /// Control
    void CLC(); // Clear Carry Flag
    void CLD(); // Clear Decimal Mode
    void CLI(); // Clear Interrupt Disable
    void CLV(); // Clear Overflow Flag
    void SEC(); // Set Carry Flag
    void SED(); // Set Decimal Mode
    void SEI(); // Set Interrupt Disable

    /// System Functions
    void BRK(); // Force Break
    void NOP(); // No Operation
    void RTI(); // Stop Execution

    /// Utils

    void set_processor_status_flag(uint8_t flag, bool value) {
        if (value) {
            P |= flag;
        } else {
            P &= ~flag;
        }
    }
};

} // cpu

#endif //CPU_H
