//
// Created by thinkPaździerż on 18.04.2025.
//

#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <array>
#include <iostream>

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

static constexpr std::uint8_t STACK_START{0xFD}; // Stack starts at 0x0100
static constexpr std::uint16_t PROGRAM_COUNTER{0xFFFC}; // Program Counter starts at 0x8000
static constexpr std::uint8_t DEFAULT_STATUS{ProcessorStatus::Unused | ProcessorStatus::InterruptDisable | ProcessorStatus::DecimalMode};
static constexpr std::uint16_t MEMORY_SIZE{0xFFFF}; // 8B * 65535 = 64KB

class CPU {
public:

    struct Instruction  {
        using InstructionHandler = void (CPU::CPU::*)();
        using AddressingModeHandler = void (CPU::CPU::*)();

        InstructionHandler instruction_handler;
        AddressingModeHandler addressing_mode_handler;
        std::uint8_t cycles;
    };
    /// Constructor

    explicit CPU(std::array<std::uint8_t, MEMORY_SIZE> & memory) : PC{PROGRAM_COUNTER}, SP{STACK_START}, A{0}, X{0}, Y{0}, memory{memory}, P{DEFAULT_STATUS} {}
    CPU(std::array<std::uint8_t, MEMORY_SIZE> & memory, const std::uint16_t PC,const std::uint8_t SP,const std::uint8_t A,const std::uint8_t X, const std::uint8_t Y,const std::uint8_t P) :
            PC{PC}, SP{SP}, A{A}, X{X}, Y{Y}, memory{memory}, P{P} {}

    [[nodiscard]] std::uint16_t get_PC()     const { return PC; }
    [[nodiscard]] std::uint8_t  get_SP()     const { return SP; }
    [[nodiscard]] std::uint8_t  get_A()      const { return A; }
    [[nodiscard]] std::uint8_t  get_X()      const { return X; }
    [[nodiscard]] std::uint8_t  get_Y()      const { return Y; }
    [[nodiscard]] std::uint8_t  get_P()      const { return P; }

    void run();
    void init();

private:
    bool after_reset{true};

    std::uint8_t cpu_cycle_delay{0};

    std::uint16_t temp_address{0};
    std::uint8_t temp_value{0};

    /// Registers
    /// https://www.nesdev.org/obelisk-6502-guide/registers.html

    std::uint16_t PC; // Program Counter
    std::uint8_t SP;  // Stack Pointer
    std::uint8_t A;   // Accumulator
    std::uint8_t X;   // Index Register X
    std::uint8_t Y;   // Index Register Y

    std::array< std::uint8_t, 0xFFFF>& memory;

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

    /// Running the CPU

    /// addressing
    void addressing_accumulator();
    void addressing_absolute();
    void addressing_absolute_x();
    void addressing_absolute_y();
    void addressing_immediate();
    void addressing_implied();
    void addressing_indirect();
    void addressing_indirect_x();
    void addressing_indirect_y();
    void addressing_relative();
    void addressing_zero_page();
    void addressing_zero_page_x();
    void addressing_zero_page_y();


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
    void PLP(); // Pull Processor Status from Stack

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
    void ASL_accumulator(); // Arithmetic Shift Left Accumulator
    void LSR(); // Logical Shift Right
    void LSR_accumulator();
    void ROL(); // Rotate Left
    void ROL_accumulator();
    void ROR(); // Rotate Right
    void ROR_accumulator();

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

    /// Utils

    void XXX(); // Illegal Instruction

    void set_processor_status_flag(std::uint8_t flag, bool value);
    bool get_processor_status_flag(std::uint8_t flag) const;

    void push_to_stack(std::uint8_t value);
    void push_to_stack(std::uint16_t value);

    template<typename T>
    T pop_from_stack();
};

} // cpu

#endif //CPU_H
