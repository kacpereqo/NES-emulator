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
};

} // cpu

#endif //CPU_H
