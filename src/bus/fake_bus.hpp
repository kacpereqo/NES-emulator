#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include "abstract_bus.hpp"

namespace Bus {
    class FakeBus final : public AbstractBus {
    public:
        explicit FakeBus(std::vector<std::uint8_t> &data, std::uint16_t start_address);

        explicit FakeBus(std::vector<std::uint8_t> &data);

        explicit FakeBus(std::array<std::uint8_t, 0x10000> &data);

        std::uint8_t cpu_read(std::uint16_t address) override;

        void cpu_write(std::uint16_t address, std::uint8_t data) override;

    private:
        std::array<std::uint8_t, 0x10000> memory{};
    };
}
