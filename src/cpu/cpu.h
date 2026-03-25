//
// Created by thinkPaździerż on 18.04.2025.
//

#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <iostream>
#include "enum.hpp"

#include "../bus/bus.hpp"

namespace CPU
{
	namespace ResetState
	{
		static constexpr std::uint8_t  SP{0xFD};   // Stack starts at 0x0100
		static constexpr std::uint16_t PC{0xFFFC}; // Program Counter starts at 0x8000
		static constexpr std::uint8_t  P{ProcessorStatus::Unused | ProcessorStatus::InterruptDisable |
                                        ProcessorStatus::DecimalMode};
		static constexpr std::uint32_t MEMORY_SIZE{0xFFFF + 1}; // 8B * 65535 = 64KB
		static constexpr std::uint8_t  A{0};
		static constexpr std::uint8_t  X{0};
		static constexpr std::uint8_t  Y{0};
	} // namespace ResetState

	static constexpr std::uint32_t MEMORY_SIZE{0xFFFF + 1}; // 8B * 65535 = 64KB

	class CPU
	{
	public:
		void set_pc(const std::uint16_t pc)
		{
			PC = pc;
		}

		struct Instruction
		{
			using InstructionHandler    = void (CPU::*)();
			using AddressingModeHandler = void (CPU::*)();

			InstructionHandler    instruction_handler;
			AddressingModeHandler addressing_mode_handler;
			std::uint8_t          cycles;
		};

		/// Constructor

		explicit CPU(Bus::AbstractBus &bus) :
		    bus{bus},
		    PC{ResetState::PC},
		    SP{ResetState::SP},
		    A{ResetState::A},
		    X{ResetState::X},
		    Y{ResetState::Y},
		    P{ResetState::P}
		{}

		CPU(Bus::AbstractBus &bus, const std::uint16_t PC, const std::uint8_t SP, const std::uint8_t A,
		    const std::uint8_t X, const std::uint8_t Y, const std::uint8_t P) :
		    bus{bus}, PC{PC}, SP{SP}, A{A}, X{X}, Y{Y}, P{P}
		{}

		[[nodiscard]] std::uint16_t get_PC() const
		{
			return PC;
		}
		[[nodiscard]] std::uint8_t get_SP() const
		{
			return SP;
		}
		[[nodiscard]] std::uint8_t get_A() const
		{
			return A;
		}
		[[nodiscard]] std::uint8_t get_X() const
		{
			return X;
		}
		[[nodiscard]] std::uint8_t get_Y() const
		{
			return Y;
		}
		[[nodiscard]] std::uint8_t get_P() const
		{
			return P;
		}

		void run();

		void init();

		void signal_nmi_interrupt();

	private:
		bool is_nmi_pending{false};
		bool after_reset{true};

		void nmi_handler();

		Bus::AbstractBus &bus;

		std::uint8_t cpu_cycle_delay{0};

		std::uint16_t temp_address{0};
		std::uint8_t  temp_value{0};

		/// Registers
		/// https://www.nesdev.org/obelisk-6502-guide/registers.html

		std::uint16_t PC; // Program Counter
		std::uint8_t  SP; // Stack Pointer
		std::uint8_t  A;  // Accumulator
		std::uint8_t  X;  // Index Register X
		std::uint8_t  Y;  // Index Register Y

		// std::array<std::uint8_t, 0xFFFF> &memory;

		std::uint8_t P; // Processor Status

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

		/// Register Transfer
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
		void ASL();             // Arithmetic Shift Left
		void ASL_accumulator(); // Arithmetic Shift Left Accumulator
		void LSR();             // Logical Shift Right
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

		static constexpr std::array<Instruction, 256> instruction_set{{
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
	};
} // namespace CPU

#endif // CPU_H
