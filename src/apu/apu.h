//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef APU_H
#define APU_H

#include <cstdint>
#include <array>


namespace APU {
    class APU {
    public:
        explicit APU(std::array<std::uint8_t, 0xFFFF> & memory) : memory{memory} {}

    private:
        std::array<std::uint8_t, 0xFFFF> & memory;

    };
}

#endif //APU_H
