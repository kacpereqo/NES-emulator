//
// Created by remza on 12.05.2025.
//

#ifndef ENUM_HPP
#define ENUM_HPP

#include <cstdint>

namespace CPU::ProcessorStatus {
enum ProcessorStatus : std::uint8_t {
  Carry = 1 << 0,
  Zero = 1 << 1,
  InterruptDisable = 1 << 2,
  DecimalMode = 1 << 3,
  BreakCommand = 1 << 4,
  Unused = 1 << 5, // 7th bit is unused
  Overflow = 1 << 6,
  Negative = 1 << 7,
};
}

#endif // ENUM_HPP
