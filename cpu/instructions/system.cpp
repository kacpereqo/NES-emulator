//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Force Break
void CPU::CPU::BRK() {
    // TODO: Implement BRK (Force Break) logic
    // This would trigger a software interrupt by pushing the Program Counter and Status flags to the stack,
    // then setting the Interrupt flag to disable further interrupts.
}

// No Operation
void CPU::CPU::NOP() {
    // TODO: Implement NOP (No Operation) logic
    // This would do nothing, just increment the Program Counter.
}

// Stop Execution (Return from Interrupt)
void CPU::CPU::RTI() {
    // TODO: Implement RTI (Return from Interrupt) logic
    // This would pop the Processor Status and Program Counter from the stack to return from an interrupt.
}
