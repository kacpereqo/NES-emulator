//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef APU_H
#define APU_H

#include <array>
#include <cmath>
#include <cstdint>

// Registers 	Channel 	Units
// $4000–$4003 	Pulse 1 	Timer, length counter, envelope, sweep
// $4004–$4007 	Pulse 2 	Timer, length counter, envelope, sweep
// $4008–$400B 	Triangle 	Timer, length counter, linear counter
// $400C–$400F 	Noise 	    Timer, length counter, envelope, linear feedback
// shift register $4010–$4013 	DMC 	    Timer, memory reader, sample buffer,
// output unit $4015 	    All 	    Channel enable and length counter
// status $4017 	    All 	    Frame counter

namespace APU {
    constexpr std::uint8_t CHANNEL_COUNT{5};

    namespace Status {
        enum Status : std::uint8_t {
            Pulse1 = 1 << 0,
            Pulse2 = 1 << 1,
            Triangle = 1 << 2,
            Noise = 1 << 3,
            DMC = 1 << 4,
        };
    }

    namespace FrameCounter {
        enum FrameCounter : std::uint8_t {
            IRQ = 1 << 6,
            Mode = 1 << 7,
        };
    }

    class APU {
    public:
        explicit APU(std::array<std::uint8_t, 0xFFFF> &memory) : memory{memory} {
            this->init();
        }

        void init() {
        }

        void run() {
        }

    private:
        std::uint8_t generate_pulse_1();

        std::uint8_t generate_pulse_2();

        std::uint8_t generate_triangle();

        std::uint8_t generate_noise();

        std::uint8_t generate_dmc();

        std::array<std::uint8_t, CHANNEL_COUNT> channels;
        std::array<std::uint8_t, 0xFFFF> &memory;
    };
} // namespace APU

#endif // APU_H