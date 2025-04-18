//
// Created by thinkPaździerż on 18.04.2025.
//

#include "../cpu.h"

// Jump to Address
void CPU::CPU::JMP(std::uint16_t address) {
    // TODO: Implement JMP (Jump) logic
    // This would update the Program Counter (PC) to the given address.
}

// Jump to Subroutine
void CPU::CPU::JSR(std::uint16_t address) {
    // TODO: Implement JSR (Jump to Subroutine) logic
    // This would push the return address (PC + 2) onto the stack and jump to the subroutine at the given address.
}

// Return from Subroutine
void CPU::CPU::RTS() {
    // TODO: Implement RTS (Return from Subroutine) logic
    // This would pop the return address from the stack and continue execution from there.
}
