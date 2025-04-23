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


TEST(CPU, instruction_AND_zero_page_x) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0xf4be;
    constexpr uint8_t SP       = 0xbf;
    constexpr uint8_t A        = 0x83;
    constexpr uint8_t X        = 0xa3;
    constexpr uint8_t Y        = 0xbc;
    constexpr uint8_t P        = 0xa3;

    memory[0xf4be] = 0x35;
    memory[0xf4bf] = 0x0c;
    memory[0xf4c0] = 0xdc;
    memory[0x000c] = 0x38;
    memory[0x00af] = 0xf6;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0xf4c0);
    EXPECT_EQ(cpu.get_SP(), 0xbf);
    EXPECT_EQ(cpu.get_A(),  0x82);
    EXPECT_EQ(cpu.get_X(),  0xa3);
    EXPECT_EQ(cpu.get_Y(),  0xbc);
    EXPECT_EQ(cpu.get_P(),  0xa1);

    EXPECT_EQ(memory[0x000c], 0x38);
    EXPECT_EQ(memory[0x00af], 0xf6);
    EXPECT_EQ(memory[0xf4be], 0x35);
    EXPECT_EQ(memory[0xf4bf], 0x0c);
    EXPECT_EQ(memory[0xf4c0], 0xdc);
}


TEST(CPU, instruction_AND_absolute_x) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0xaaac;
    constexpr uint8_t SP       = 0x0e;
    constexpr uint8_t A        = 0x3a;
    constexpr uint8_t X        = 0xdf;
    constexpr uint8_t Y        = 0x94;
    constexpr uint8_t P        = 0x6b;

    memory[0xaaac] = 0x3d;
    memory[0xaaad] = 0x20;
    memory[0xaaae] = 0x00;
    memory[0x00ff] = 0x44;
    memory[0xaaaf] = 0x45;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0xaaaf);
    EXPECT_EQ(cpu.get_SP(), 0x0e);
    EXPECT_EQ(cpu.get_A(),  0x00);
    EXPECT_EQ(cpu.get_X(),  0xdf);
    EXPECT_EQ(cpu.get_Y(),  0x94);
    EXPECT_EQ(cpu.get_P(),  0x6b);

    EXPECT_EQ(memory[0x00ff], 0x44);
    EXPECT_EQ(memory[0xaaac], 0x3d);
    EXPECT_EQ(memory[0xaaad], 0x20);
    EXPECT_EQ(memory[0xaaae], 0x00);
    EXPECT_EQ(memory[0xaaaf], 0x45);
}


TEST(CPU, instruction_AND_absolute_y) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0xe59a;
    constexpr uint8_t SP       = 0xc8;
    constexpr uint8_t A        = 0x91;
    constexpr uint8_t X        = 0x4d;
    constexpr uint8_t Y        = 0x80;
    constexpr uint8_t P        = 0xa2;

    memory[0xe59a] = 0x39;
    memory[0xe59b] = 0x94;
    memory[0xe59c] = 0xf0;
    memory[0xf014] = 0x23;
    memory[0xf114] = 0xe5;
    memory[0xe59d] = 0x98;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0xe59d);
    EXPECT_EQ(cpu.get_SP(), 0xc8);
    EXPECT_EQ(cpu.get_A(),  0x81);
    EXPECT_EQ(cpu.get_X(),  0x4d);
    EXPECT_EQ(cpu.get_Y(),  0x80);
    EXPECT_EQ(cpu.get_P(),  0xa0);

    EXPECT_EQ(memory[0xe59a], 0x39);
    EXPECT_EQ(memory[0xe59b], 0x94);
    EXPECT_EQ(memory[0xe59c], 0xf0);
    EXPECT_EQ(memory[0xe59d], 0x98);
    EXPECT_EQ(memory[0xf014], 0x23);
    EXPECT_EQ(memory[0xf114], 0xe5);
}


TEST(CPU, instruction_AND_indirect_x) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0x1672;
    constexpr uint8_t SP       = 0x51;
    constexpr uint8_t A        = 0x32;
    constexpr uint8_t X        = 0xef;
    constexpr uint8_t Y        = 0xf1;
    constexpr uint8_t P        = 0xa4;

    memory[0x1672] = 0x21;
    memory[0x1673] = 0xb7;
    memory[0x1674] = 0xa2;
    memory[0x00b7] = 0xf6;
    memory[0x00a6] = 0x14;
    memory[0x00a7] = 0xd4;
    memory[0xd414] = 0x99;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0x1674);
    EXPECT_EQ(cpu.get_SP(), 0x51);
    EXPECT_EQ(cpu.get_A(),  0x10);
    EXPECT_EQ(cpu.get_X(),  0xef);
    EXPECT_EQ(cpu.get_Y(),  0xf1);
    EXPECT_EQ(cpu.get_P(),  0x24);

    EXPECT_EQ(memory[0x00a6], 0x14);
    EXPECT_EQ(memory[0x00a7], 0xd4);
    EXPECT_EQ(memory[0x00b7], 0xf6);
    EXPECT_EQ(memory[0x1672], 0x21);
    EXPECT_EQ(memory[0x1673], 0xb7);
    EXPECT_EQ(memory[0x1674], 0xa2);
    EXPECT_EQ(memory[0xd414], 0x99);
}

TEST(CPU, instruction_AND_indirect_y) {
    std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

    constexpr std::uint16_t PC = 0x5bc8;
    constexpr uint8_t SP       = 0x4f;
    constexpr uint8_t A        = 0x7d;
    constexpr uint8_t X        = 0xd2;
    constexpr uint8_t Y        = 0x5f;
    constexpr uint8_t P        = 0xae;

    memory[0x5bc8] = 0x31;
    memory[0x5bc9] = 0xd3;
    memory[0x5bca] = 0x21;
    memory[0x00d3] = 0x5c;
    memory[0x00d4] = 0x09;
    memory[0x09bb] = 0x6d;

    CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

    cpu.run();

    EXPECT_EQ(cpu.get_PC(), 0x5bca);
    EXPECT_EQ(cpu.get_SP(), 0x4f);
    EXPECT_EQ(cpu.get_A(),  0x6d);
    EXPECT_EQ(cpu.get_X(),  0xd2);
    EXPECT_EQ(cpu.get_Y(),  0x5f);
    EXPECT_EQ(cpu.get_P(),  0x2c);

    EXPECT_EQ(memory[0x00d3], 0x5c);
    EXPECT_EQ(memory[0x00d4], 0x09);
    EXPECT_EQ(memory[0x09bb], 0x6d);
    EXPECT_EQ(memory[0x5bc8], 0x31);
    EXPECT_EQ(memory[0x5bc9], 0xd3);
    EXPECT_EQ(memory[0x5bca], 0x21);
}
