//
// Created by thinkPaździerż on 18.04.2025.
//

#include <cstdint>

#ifndef CPU_H
#define CPU_H

namespace CPU {

enum class ProcessorStatus {
    Carry            = 1 << 0,
    Zero             = 1 << 1,
    InterruptDisable = 1 << 2,
    DecimalMode      = 1 << 3,
    BreakCommand     = 1 << 4,
    Overflow         = 1 << 6,
    Negative         = 1 << 7,
};

class CPU {
    /// Registers
    /// https://www.nesdev.org/obelisk-6502-guide/registers.html

    std::uint16_t PC; // Program Counter
    std::uint8_t SP;  // Stack Pointer
    std::uint8_t A;   // Accumulator
    std::uint8_t X;   // Index Register X
    std::uint8_t Y;   // Index Register Y

    std::uint8_t P;   // Processor Status

    /// Constructor

    CPU() : PC(0), SP(0), A(0), X(0), Y(0), P(0) {}


    /// Instructions

    /// Load/Store
    void LDA(); // Load Accumulator
    void LDX(); // Load Index Register X
    void LDY(); // Load Index Register Y
    void STA(); // Store Accumulator
    void STX(); // Store Index Register X
    void STY(); // Store Index Register Y

    ///Register Transfer
    void TAX(); // Transfer Accumulator to Index Register X
    void TAY(); // Transfer Accumulator to Index Register Y
    void TXA(); // Transfer Stack Pointer to Index Register X
    void TYA(); // Transfer Index Register X to Accumulator

    /// Stack Operations
    void TSX(); // Transfer Stack Pointer to Index Register X
    void TXS(); // Transfer Index Register X to Stack Pointer
    void PHA(); // Push Accumulator on Stack
    void PHP(); // Push Processor Status on Stack
    void PLA(); // Pull Accumulator from Stack

    /// Logical
    void AND(); // Logical AND
    void ORA(); // Logical OR
    void EOR(); // Logical XOR
    void BIT(); // Bit Test

    /// Arithmetic
    void ADC(); // Add with Carry
    void SBC(); // Subtract with Carry
    void CMP(); // Compare Accumulator
    void CPX(); // Compare Index Register X
    void CPY(); // Compare Index Register Y

    /// Increments & Decrements
    void INC(); // Increment Memory
    void INX(); // Increment Index Register X
    void INY(); // Increment Index Register Y
    void DEC(); // Decrement Memory
    void DEX(); // Decrement Index Register X
    void DEY(); // Decrement Index Register Y

    /// Shifts
    void ASL(); // Arithmetic Shift Left
    void LSR(); // Logical Shift Right
    void ROL(); // Rotate Left
    void ROR(); // Rotate Right

    /// Jumps & Calls
    void JMP(); // Jump to Address
    void JSR(); // Jump to Subroutine
    void RTS(); // Return from Subroutine

    /// Branches
    void BCC(); // Branch if Equal
    void BCS(); // Branch if Carry Set
    void BEQ(); // Branch if Equal
    void BMI(); // Branch if Minus
    void BNE(); // Branch if Not Equal
    void BPL(); // Branch if Positive
    void BVC(); // Branch if Overflow Clear
    void BVS(); // Branch if Overflow Set

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
};

} // cpu

#endif //CPU_H
