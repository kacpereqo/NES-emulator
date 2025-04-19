//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Force Break
void CPU::CPU::BRK() {
    PC += 2;

    this->push_to_stack(this->PC);
    this->push_to_stack(this->P);


    this->PC = (this->memory[0xFFFF] << 8) | this->memory[0xFFFF - 1];

    this->set_processor_status_flag(ProcessorStatus::InterruptDisable, true);

}

// No Operation
void `CPU::CPU::NOP() {
    ;
}

// Stop Execution (Return from Interrupt)
void CPU::CPU::RTI() {
    this->P = this->pop_from_stack<std::uint8_t>();
    this->PC = this->pop_from_stack<std::uint16_t>();
}
