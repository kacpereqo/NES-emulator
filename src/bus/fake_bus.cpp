#include "fake_bus.hpp"

#include <algorithm>
#include <iostream>

namespace Bus {
    FakeBus::FakeBus(std::vector<std::uint8_t> &data, std::uint16_t start_address) {
        std::ranges::copy(data, memory.begin() + start_address);
        std::cout << "FakeBus: " << std::hex << start_address << std::endl;
    }

    FakeBus::FakeBus(std::vector<std::uint8_t> &data) {
        std::ranges::copy(data, memory.begin());
    }

    FakeBus::FakeBus(std::array<std::uint8_t, 0x10000> &data) {
        std::ranges::copy(data, memory.begin());
    }

    std::uint8_t FakeBus::cpu_read(const std::uint16_t address) {
        return memory[address];
    }

    void FakeBus::cpu_write(const std::uint16_t address, const std::uint8_t data) {
        memory[address] = data;
    }
}
