//
// Created by thinkPaździerż on 21.04.2025.
//
#include <gtest/gtest.h>
#include "../cpu.h"

// Demonstrate some basic assertions.
TEST(CPU, initial_state) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
    const CPU::CPU cpu{memory};

    EXPECT_EQ(cpu.get_PC(), CPU::PROGRAM_COUNTER);
    EXPECT_EQ(cpu.get_SP(), CPU::STACK_START);
    EXPECT_EQ(cpu.get_A(), 0);
    EXPECT_EQ(cpu.get_X(), 0);
    EXPECT_EQ(cpu.get_Y(), 0);
    EXPECT_EQ(cpu.get_P(), CPU::DEFAULT_STATUS);
}

TEST(CPU, read_pc_vector_table) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
    CPU::CPU cpu{memory};

    memory[0xFFFC] = 0x00; // Low byte of the reset vector
    memory[0xFFFD] = 0x80; // High byte of the reset vector

    cpu.init();

    EXPECT_EQ(cpu.get_PC(), 0x8000);
}

TEST(CPU, instruction_00) {
    GTEST_SKIP() << "Instruction 00 not implemented" << std::endl;
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
    constexpr std::uint16_t PC{35714};
    constexpr uint8_t SP{81};
    constexpr uint8_t A{203};
    constexpr uint8_t X{117};
    constexpr uint8_t Y{162};
    constexpr uint8_t P{106};

    memory[35714] = 0;
    memory[35715] = 63;
    memory[35716] = 247;
    memory[65534] = 212;
    memory[65535] = 37;
    memory[9684] = 237;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 9684);
    EXPECT_EQ(cpu.get_SP(), 78);
    EXPECT_EQ(cpu.get_A(), 203);
    EXPECT_EQ(cpu.get_X(), 117);
    EXPECT_EQ(cpu.get_Y(), 162);
    EXPECT_EQ(cpu.get_P(), 110);

    EXPECT_EQ(memory[335], 122);
    EXPECT_EQ(memory[336], 132);
    EXPECT_EQ(memory[337], 139);
    EXPECT_EQ(memory[9684], 237);
    EXPECT_EQ(memory[35714], 0);
    EXPECT_EQ(memory[35715], 63);
    EXPECT_EQ(memory[35716], 247);
    EXPECT_EQ(memory[65534], 212);
    EXPECT_EQ(memory[65535], 37);
}

TEST(CPU, instruction_inc_zero_page_indirect) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 41919;
    constexpr uint8_t SP = 18;
    constexpr uint8_t A = 0;
    constexpr uint8_t X = 194;
    constexpr uint8_t Y = 119;
    constexpr uint8_t P = 46;

    // Setup initial memory
    memory[41919] = 0xE6; // Assuming this is INC instruction
    memory[41920] = 0xE4;
    memory[41921] = 0x2D;
    memory[0x00E4] = 0xC9; // 201

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 41921);
    EXPECT_EQ(cpu.get_SP(), 18);
    EXPECT_EQ(cpu.get_A(), 0);
    EXPECT_EQ(cpu.get_X(), 194);
    EXPECT_EQ(cpu.get_Y(), 119);
    EXPECT_EQ(cpu.get_P(), 172); // Flags after INC (possibly N set)

    EXPECT_EQ(memory[0x00E4], 0xCA); // 202
    EXPECT_EQ(memory[41919], 0xE6);
    EXPECT_EQ(memory[41920], 0xE4);
    EXPECT_EQ(memory[41921], 0x2D);
}

TEST(CPU, instruction_AND_immediate) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0xa4c7;
    constexpr uint8_t SP       = 0x1d;
    constexpr uint8_t A        = 0xb0;
    constexpr uint8_t X        = 0x88;
    constexpr uint8_t Y        = 0x4b;
    constexpr uint8_t P        = 0x22;

    memory[0xa4c7] = 0x29;
    memory[0xa4c8] = 0x14;
    memory[0xa4c9] = 0xc3;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0xa4c9);
    EXPECT_EQ(cpu.get_SP(), 0x1d);
    EXPECT_EQ(cpu.get_A(),  0x10);
    EXPECT_EQ(cpu.get_X(),  0x88);
    EXPECT_EQ(cpu.get_Y(),  0x4b);
    EXPECT_EQ(cpu.get_P(),  0x20);

    EXPECT_EQ(memory[0xa4c7], 0x29);
    EXPECT_EQ(memory[0xa4c8], 0x14);
    EXPECT_EQ(memory[0xa4c9], 0xc3);
}


TEST(CPU, instruction_AND_zero_page) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0xf0a2;
    constexpr uint8_t SP       = 0x19;
    constexpr uint8_t A        = 0x37;
    constexpr uint8_t X        = 0xad;
    constexpr uint8_t Y        = 0xb4;
    constexpr uint8_t P        = 0xab;

    memory[0xf0a2] = 0x25;
    memory[0xf0a3] = 0xda;
    memory[0xf0a4] = 0x5a;
    memory[0x00da] = 0xfc;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0xf0a4);
    EXPECT_EQ(cpu.get_SP(), 0x19);
    EXPECT_EQ(cpu.get_A(),  0x34);
    EXPECT_EQ(cpu.get_X(),  0xad);
    EXPECT_EQ(cpu.get_Y(),  0xb4);
    EXPECT_EQ(cpu.get_P(),  0x29);

    EXPECT_EQ(memory[0x00da], 0xfc);
    EXPECT_EQ(memory[0xf0a2], 0x25);
    EXPECT_EQ(memory[0xf0a3], 0xda);
    EXPECT_EQ(memory[0xf0a4], 0x5a);
}
