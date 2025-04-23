//
// Created by thinkPaździerż on 21.04.2025.
//
#include "../cpu.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(CPU, initial_state) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  const CPU::CPU cpu{memory};

  // Test the initial state of the CPU
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

  // Test the initial state of the CPU
  cpu.init();

  EXPECT_EQ(cpu.get_PC(), 0x8000);
}

TEST(CPU, instruction_BRK_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x00";

  constexpr std::uint16_t PC = 0x8b82;
  constexpr uint8_t SP = 0x51;
  constexpr uint8_t A = 0xcb;
  constexpr uint8_t X = 0x75;
  constexpr uint8_t Y = 0xa2;
  constexpr uint8_t P = 0x6a;

  memory[0x8b82] = 0x00;
  memory[0x8b83] = 0x3f;
  memory[0x8b84] = 0xf7;
  memory[0xfffe] = 0xd4;
  memory[0xffff] = 0x25;
  memory[0x25d4] = 0xed;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x25d4);
  EXPECT_EQ(cpu.get_SP(), 0x4e);
  EXPECT_EQ(cpu.get_A(), 0xcb);
  EXPECT_EQ(cpu.get_X(), 0x75);
  EXPECT_EQ(cpu.get_Y(), 0xa2);
  EXPECT_EQ(cpu.get_P(), 0x6e);

  EXPECT_EQ(memory[0x014f], 0x7a);
  EXPECT_EQ(memory[0x0150], 0x84);
  EXPECT_EQ(memory[0x0151], 0x8b);
  EXPECT_EQ(memory[0x25d4], 0xed);
  EXPECT_EQ(memory[0x8b82], 0x00);
  EXPECT_EQ(memory[0x8b83], 0x3f);
  EXPECT_EQ(memory[0x8b84], 0xf7);
  EXPECT_EQ(memory[0xfffe], 0xd4);
  EXPECT_EQ(memory[0xffff], 0x25);
}
TEST(CPU, instruction_ORA_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x01";

  constexpr std::uint16_t PC = 0xd5c4;
  constexpr uint8_t SP = 0x61;
  constexpr uint8_t A = 0xa7;
  constexpr uint8_t X = 0xf7;
  constexpr uint8_t Y = 0xf8;
  constexpr uint8_t P = 0x28;

  memory[0xd5c4] = 0x01;
  memory[0xd5c5] = 0xbd;
  memory[0xd5c6] = 0xb0;
  memory[0x00bd] = 0x58;
  memory[0x00b4] = 0x81;
  memory[0x00b5] = 0xeb;
  memory[0xeb81] = 0x13;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd5c6);
  EXPECT_EQ(cpu.get_SP(), 0x61);
  EXPECT_EQ(cpu.get_A(), 0xb7);
  EXPECT_EQ(cpu.get_X(), 0xf7);
  EXPECT_EQ(cpu.get_Y(), 0xf8);
  EXPECT_EQ(cpu.get_P(), 0xa8);

  EXPECT_EQ(memory[0x00b4], 0x81);
  EXPECT_EQ(memory[0x00b5], 0xeb);
  EXPECT_EQ(memory[0x00bd], 0x58);
  EXPECT_EQ(memory[0xd5c4], 0x01);
  EXPECT_EQ(memory[0xd5c5], 0xbd);
  EXPECT_EQ(memory[0xd5c6], 0xb0);
  EXPECT_EQ(memory[0xeb81], 0x13);
}
TEST(CPU, instruction_ORA_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x05";

  constexpr std::uint16_t PC = 0x4d71;
  constexpr uint8_t SP = 0xa5;
  constexpr uint8_t A = 0xfa;
  constexpr uint8_t X = 0x19;
  constexpr uint8_t Y = 0x04;
  constexpr uint8_t P = 0x23;

  memory[0x4d71] = 0x05;
  memory[0x4d72] = 0xca;
  memory[0x4d73] = 0x36;
  memory[0x00ca] = 0xa5;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4d73);
  EXPECT_EQ(cpu.get_SP(), 0xa5);
  EXPECT_EQ(cpu.get_A(), 0xff);
  EXPECT_EQ(cpu.get_X(), 0x19);
  EXPECT_EQ(cpu.get_Y(), 0x04);
  EXPECT_EQ(cpu.get_P(), 0xa1);

  EXPECT_EQ(memory[0x00ca], 0xa5);
  EXPECT_EQ(memory[0x4d71], 0x05);
  EXPECT_EQ(memory[0x4d72], 0xca);
  EXPECT_EQ(memory[0x4d73], 0x36);
}
TEST(CPU, instruction_ASL_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x06";

  constexpr std::uint16_t PC = 0xec81;
  constexpr uint8_t SP = 0x56;
  constexpr uint8_t A = 0xaa;
  constexpr uint8_t X = 0xdd;
  constexpr uint8_t Y = 0xba;
  constexpr uint8_t P = 0x29;

  memory[0xec81] = 0x06;
  memory[0xec82] = 0x89;
  memory[0xec83] = 0x7c;
  memory[0x0089] = 0x42;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xec83);
  EXPECT_EQ(cpu.get_SP(), 0x56);
  EXPECT_EQ(cpu.get_A(), 0xaa);
  EXPECT_EQ(cpu.get_X(), 0xdd);
  EXPECT_EQ(cpu.get_Y(), 0xba);
  EXPECT_EQ(cpu.get_P(), 0xa8);

  EXPECT_EQ(memory[0x0089], 0x84);
  EXPECT_EQ(memory[0xec81], 0x06);
  EXPECT_EQ(memory[0xec82], 0x89);
  EXPECT_EQ(memory[0xec83], 0x7c);
}
TEST(CPU, instruction_PHP_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x08";

  constexpr std::uint16_t PC = 0x2f81;
  constexpr uint8_t SP = 0x26;
  constexpr uint8_t A = 0x87;
  constexpr uint8_t X = 0x6a;
  constexpr uint8_t Y = 0xb4;
  constexpr uint8_t P = 0x2b;

  memory[0x2f81] = 0x08;
  memory[0x2f82] = 0x60;
  memory[0x2f83] = 0xbe;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x2f82);
  EXPECT_EQ(cpu.get_SP(), 0x25);
  EXPECT_EQ(cpu.get_A(), 0x87);
  EXPECT_EQ(cpu.get_X(), 0x6a);
  EXPECT_EQ(cpu.get_Y(), 0xb4);
  EXPECT_EQ(cpu.get_P(), 0x2b);

  EXPECT_EQ(memory[0x0126], 0x3b);
  EXPECT_EQ(memory[0x2f81], 0x08);
  EXPECT_EQ(memory[0x2f82], 0x60);
  EXPECT_EQ(memory[0x2f83], 0xbe);
}
TEST(CPU, instruction_ORA_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x09";

  constexpr std::uint16_t PC = 0xb1b7;
  constexpr uint8_t SP = 0x12;
  constexpr uint8_t A = 0xa0;
  constexpr uint8_t X = 0xdc;
  constexpr uint8_t Y = 0x39;
  constexpr uint8_t P = 0xad;

  memory[0xb1b7] = 0x09;
  memory[0xb1b8] = 0xfb;
  memory[0xb1b9] = 0xcb;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xb1b9);
  EXPECT_EQ(cpu.get_SP(), 0x12);
  EXPECT_EQ(cpu.get_A(), 0xfb);
  EXPECT_EQ(cpu.get_X(), 0xdc);
  EXPECT_EQ(cpu.get_Y(), 0x39);
  EXPECT_EQ(cpu.get_P(), 0xad);

  EXPECT_EQ(memory[0xb1b7], 0x09);
  EXPECT_EQ(memory[0xb1b8], 0xfb);
  EXPECT_EQ(memory[0xb1b9], 0xcb);
}
TEST(CPU, instruction_ASL_accumulator) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x0a";

  constexpr std::uint16_t PC = 0xd91a;
  constexpr uint8_t SP = 0x8e;
  constexpr uint8_t A = 0x39;
  constexpr uint8_t X = 0x3e;
  constexpr uint8_t Y = 0x5d;
  constexpr uint8_t P = 0xab;

  memory[0xd91a] = 0x0a;
  memory[0xd91b] = 0x78;
  memory[0xd91c] = 0x2d;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd91b);
  EXPECT_EQ(cpu.get_SP(), 0x8e);
  EXPECT_EQ(cpu.get_A(), 0x72);
  EXPECT_EQ(cpu.get_X(), 0x3e);
  EXPECT_EQ(cpu.get_Y(), 0x5d);
  EXPECT_EQ(cpu.get_P(), 0x28);

  EXPECT_EQ(memory[0xd91a], 0x0a);
  EXPECT_EQ(memory[0xd91b], 0x78);
  EXPECT_EQ(memory[0xd91c], 0x2d);
}
TEST(CPU, instruction_ORA_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x0d";

  constexpr std::uint16_t PC = 0xa81f;
  constexpr uint8_t SP = 0xf9;
  constexpr uint8_t A = 0x27;
  constexpr uint8_t X = 0xe4;
  constexpr uint8_t Y = 0x5a;
  constexpr uint8_t P = 0xe8;

  memory[0xa81f] = 0x0d;
  memory[0xa820] = 0x63;
  memory[0xa821] = 0x46;
  memory[0x4663] = 0xe5;
  memory[0xa822] = 0x28;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa822);
  EXPECT_EQ(cpu.get_SP(), 0xf9);
  EXPECT_EQ(cpu.get_A(), 0xe7);
  EXPECT_EQ(cpu.get_X(), 0xe4);
  EXPECT_EQ(cpu.get_Y(), 0x5a);
  EXPECT_EQ(cpu.get_P(), 0xe8);

  EXPECT_EQ(memory[0x4663], 0xe5);
  EXPECT_EQ(memory[0xa81f], 0x0d);
  EXPECT_EQ(memory[0xa820], 0x63);
  EXPECT_EQ(memory[0xa821], 0x46);
  EXPECT_EQ(memory[0xa822], 0x28);
}
TEST(CPU, instruction_ASL_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x0e";

  constexpr std::uint16_t PC = 0xabba;
  constexpr uint8_t SP = 0x45;
  constexpr uint8_t A = 0xd9;
  constexpr uint8_t X = 0xf4;
  constexpr uint8_t Y = 0x1c;
  constexpr uint8_t P = 0x68;

  memory[0xabba] = 0x0e;
  memory[0xabbb] = 0x16;
  memory[0xabbc] = 0xe0;
  memory[0xe016] = 0x0a;
  memory[0xabbd] = 0x8d;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xabbd);
  EXPECT_EQ(cpu.get_SP(), 0x45);
  EXPECT_EQ(cpu.get_A(), 0xd9);
  EXPECT_EQ(cpu.get_X(), 0xf4);
  EXPECT_EQ(cpu.get_Y(), 0x1c);
  EXPECT_EQ(cpu.get_P(), 0x68);

  EXPECT_EQ(memory[0xabba], 0x0e);
  EXPECT_EQ(memory[0xabbb], 0x16);
  EXPECT_EQ(memory[0xabbc], 0xe0);
  EXPECT_EQ(memory[0xabbd], 0x8d);
  EXPECT_EQ(memory[0xe016], 0x14);
}
TEST(CPU, instruction_BPL_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x10";

  constexpr std::uint16_t PC = 0x4484;
  constexpr uint8_t SP = 0xf8;
  constexpr uint8_t A = 0xd5;
  constexpr uint8_t X = 0xf9;
  constexpr uint8_t Y = 0xe0;
  constexpr uint8_t P = 0xaa;

  memory[0x4484] = 0x10;
  memory[0x4485] = 0x36;
  memory[0x4486] = 0xa8;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4486);
  EXPECT_EQ(cpu.get_SP(), 0xf8);
  EXPECT_EQ(cpu.get_A(), 0xd5);
  EXPECT_EQ(cpu.get_X(), 0xf9);
  EXPECT_EQ(cpu.get_Y(), 0xe0);
  EXPECT_EQ(cpu.get_P(), 0xaa);

  EXPECT_EQ(memory[0x4484], 0x10);
  EXPECT_EQ(memory[0x4485], 0x36);
  EXPECT_EQ(memory[0x4486], 0xa8);
}
TEST(CPU, instruction_ORA_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x11";

  constexpr std::uint16_t PC = 0xf4ef;
  constexpr uint8_t SP = 0x84;
  constexpr uint8_t A = 0xb6;
  constexpr uint8_t X = 0xd2;
  constexpr uint8_t Y = 0x75;
  constexpr uint8_t P = 0x64;

  memory[0xf4ef] = 0x11;
  memory[0xf4f0] = 0xb6;
  memory[0xf4f1] = 0x00;
  memory[0x00b6] = 0xfd;
  memory[0x00b7] = 0xb6;
  memory[0xb672] = 0x3e;
  memory[0xb772] = 0x15;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xf4f1);
  EXPECT_EQ(cpu.get_SP(), 0x84);
  EXPECT_EQ(cpu.get_A(), 0xb7);
  EXPECT_EQ(cpu.get_X(), 0xd2);
  EXPECT_EQ(cpu.get_Y(), 0x75);
  EXPECT_EQ(cpu.get_P(), 0xe4);

  EXPECT_EQ(memory[0x00b6], 0xfd);
  EXPECT_EQ(memory[0x00b7], 0xb6);
  EXPECT_EQ(memory[0xb672], 0x3e);
  EXPECT_EQ(memory[0xb772], 0x15);
  EXPECT_EQ(memory[0xf4ef], 0x11);
  EXPECT_EQ(memory[0xf4f0], 0xb6);
  EXPECT_EQ(memory[0xf4f1], 0x00);
}
TEST(CPU, instruction_ORA_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x15";

  constexpr std::uint16_t PC = 0xf50d;
  constexpr uint8_t SP = 0xdb;
  constexpr uint8_t A = 0x6f;
  constexpr uint8_t X = 0x56;
  constexpr uint8_t Y = 0xe4;
  constexpr uint8_t P = 0xa9;

  memory[0xf50d] = 0x15;
  memory[0xf50e] = 0x22;
  memory[0xf50f] = 0x30;
  memory[0x0022] = 0x51;
  memory[0x0078] = 0xf1;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xf50f);
  EXPECT_EQ(cpu.get_SP(), 0xdb);
  EXPECT_EQ(cpu.get_A(), 0xff);
  EXPECT_EQ(cpu.get_X(), 0x56);
  EXPECT_EQ(cpu.get_Y(), 0xe4);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x0022], 0x51);
  EXPECT_EQ(memory[0x0078], 0xf1);
  EXPECT_EQ(memory[0xf50d], 0x15);
  EXPECT_EQ(memory[0xf50e], 0x22);
  EXPECT_EQ(memory[0xf50f], 0x30);
}
TEST(CPU, instruction_ASL_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x16";

  constexpr std::uint16_t PC = 0xe4fd;
  constexpr uint8_t SP = 0x66;
  constexpr uint8_t A = 0xac;
  constexpr uint8_t X = 0xae;
  constexpr uint8_t Y = 0x5f;
  constexpr uint8_t P = 0x6f;

  memory[0xe4fd] = 0x16;
  memory[0xe4fe] = 0x26;
  memory[0xe4ff] = 0x59;
  memory[0x0026] = 0x12;
  memory[0x00d4] = 0xd2;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xe4ff);
  EXPECT_EQ(cpu.get_SP(), 0x66);
  EXPECT_EQ(cpu.get_A(), 0xac);
  EXPECT_EQ(cpu.get_X(), 0xae);
  EXPECT_EQ(cpu.get_Y(), 0x5f);
  EXPECT_EQ(cpu.get_P(), 0xed);

  EXPECT_EQ(memory[0x0026], 0x12);
  EXPECT_EQ(memory[0x00d4], 0xa4);
  EXPECT_EQ(memory[0xe4fd], 0x16);
  EXPECT_EQ(memory[0xe4fe], 0x26);
  EXPECT_EQ(memory[0xe4ff], 0x59);
}
TEST(CPU, instruction_CLC_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x18";

  constexpr std::uint16_t PC = 0x09a8;
  constexpr uint8_t SP = 0x26;
  constexpr uint8_t A = 0xd7;
  constexpr uint8_t X = 0x79;
  constexpr uint8_t Y = 0xbf;
  constexpr uint8_t P = 0xec;

  memory[0x09a8] = 0x18;
  memory[0x09a9] = 0xc9;
  memory[0x09aa] = 0x9b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x09a9);
  EXPECT_EQ(cpu.get_SP(), 0x26);
  EXPECT_EQ(cpu.get_A(), 0xd7);
  EXPECT_EQ(cpu.get_X(), 0x79);
  EXPECT_EQ(cpu.get_Y(), 0xbf);
  EXPECT_EQ(cpu.get_P(), 0xec);

  EXPECT_EQ(memory[0x09a8], 0x18);
  EXPECT_EQ(memory[0x09a9], 0xc9);
  EXPECT_EQ(memory[0x09aa], 0x9b);
}
TEST(CPU, instruction_ORA_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x19";

  constexpr std::uint16_t PC = 0xf09b;
  constexpr uint8_t SP = 0x81;
  constexpr uint8_t A = 0x52;
  constexpr uint8_t X = 0x21;
  constexpr uint8_t Y = 0x86;
  constexpr uint8_t P = 0xe6;

  memory[0xf09b] = 0x19;
  memory[0xf09c] = 0x12;
  memory[0xf09d] = 0x52;
  memory[0x5298] = 0xf2;
  memory[0xf09e] = 0xac;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xf09e);
  EXPECT_EQ(cpu.get_SP(), 0x81);
  EXPECT_EQ(cpu.get_A(), 0xf2);
  EXPECT_EQ(cpu.get_X(), 0x21);
  EXPECT_EQ(cpu.get_Y(), 0x86);
  EXPECT_EQ(cpu.get_P(), 0xe4);

  EXPECT_EQ(memory[0x5298], 0xf2);
  EXPECT_EQ(memory[0xf09b], 0x19);
  EXPECT_EQ(memory[0xf09c], 0x12);
  EXPECT_EQ(memory[0xf09d], 0x52);
  EXPECT_EQ(memory[0xf09e], 0xac);
}
TEST(CPU, instruction_ORA_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x1d";

  constexpr std::uint16_t PC = 0xcc0a;
  constexpr uint8_t SP = 0x02;
  constexpr uint8_t A = 0xd8;
  constexpr uint8_t X = 0x8e;
  constexpr uint8_t Y = 0x05;
  constexpr uint8_t P = 0x29;

  memory[0xcc0a] = 0x1d;
  memory[0xcc0b] = 0xb5;
  memory[0xcc0c] = 0x10;
  memory[0x1043] = 0x4a;
  memory[0x1143] = 0xd4;
  memory[0xcc0d] = 0xf8;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xcc0d);
  EXPECT_EQ(cpu.get_SP(), 0x02);
  EXPECT_EQ(cpu.get_A(), 0xdc);
  EXPECT_EQ(cpu.get_X(), 0x8e);
  EXPECT_EQ(cpu.get_Y(), 0x05);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x1043], 0x4a);
  EXPECT_EQ(memory[0x1143], 0xd4);
  EXPECT_EQ(memory[0xcc0a], 0x1d);
  EXPECT_EQ(memory[0xcc0b], 0xb5);
  EXPECT_EQ(memory[0xcc0c], 0x10);
  EXPECT_EQ(memory[0xcc0d], 0xf8);
}
TEST(CPU, instruction_ASL_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x1e";

  constexpr std::uint16_t PC = 0x4f7a;
  constexpr uint8_t SP = 0xdc;
  constexpr uint8_t A = 0xfa;
  constexpr uint8_t X = 0x6e;
  constexpr uint8_t Y = 0x94;
  constexpr uint8_t P = 0x6d;

  memory[0x4f7a] = 0x1e;
  memory[0x4f7b] = 0xb1;
  memory[0x4f7c] = 0x05;
  memory[0x051f] = 0xf6;
  memory[0x061f] = 0xf1;
  memory[0x4f7d] = 0x8a;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4f7d);
  EXPECT_EQ(cpu.get_SP(), 0xdc);
  EXPECT_EQ(cpu.get_A(), 0xfa);
  EXPECT_EQ(cpu.get_X(), 0x6e);
  EXPECT_EQ(cpu.get_Y(), 0x94);
  EXPECT_EQ(cpu.get_P(), 0xed);

  EXPECT_EQ(memory[0x051f], 0xf6);
  EXPECT_EQ(memory[0x061f], 0xe2);
  EXPECT_EQ(memory[0x4f7a], 0x1e);
  EXPECT_EQ(memory[0x4f7b], 0xb1);
  EXPECT_EQ(memory[0x4f7c], 0x05);
  EXPECT_EQ(memory[0x4f7d], 0x8a);
}
TEST(CPU, instruction_JSR_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x20";

  constexpr std::uint16_t PC = 0x5289;
  constexpr uint8_t SP = 0x3e;
  constexpr uint8_t A = 0xc2;
  constexpr uint8_t X = 0x2d;
  constexpr uint8_t Y = 0x3e;
  constexpr uint8_t P = 0x6e;

  memory[0x5289] = 0x20;
  memory[0x528a] = 0xc2;
  memory[0x528b] = 0x8f;
  memory[0x013e] = 0x9b;
  memory[0x8fc2] = 0xc8;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x8fc2);
  EXPECT_EQ(cpu.get_SP(), 0x3c);
  EXPECT_EQ(cpu.get_A(), 0xc2);
  EXPECT_EQ(cpu.get_X(), 0x2d);
  EXPECT_EQ(cpu.get_Y(), 0x3e);
  EXPECT_EQ(cpu.get_P(), 0x6e);

  EXPECT_EQ(memory[0x013d], 0x8b);
  EXPECT_EQ(memory[0x013e], 0x52);
  EXPECT_EQ(memory[0x5289], 0x20);
  EXPECT_EQ(memory[0x528a], 0xc2);
  EXPECT_EQ(memory[0x528b], 0x8f);
  EXPECT_EQ(memory[0x8fc2], 0xc8);
}
TEST(CPU, instruction_AND_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x1672;
  constexpr uint8_t SP = 0x51;
  constexpr uint8_t A = 0x32;
  constexpr uint8_t X = 0xef;
  constexpr uint8_t Y = 0xf1;
  constexpr uint8_t P = 0xa4;

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
  EXPECT_EQ(cpu.get_A(), 0x10);
  EXPECT_EQ(cpu.get_X(), 0xef);
  EXPECT_EQ(cpu.get_Y(), 0xf1);
  EXPECT_EQ(cpu.get_P(), 0x24);

  EXPECT_EQ(memory[0x00a6], 0x14);
  EXPECT_EQ(memory[0x00a7], 0xd4);
  EXPECT_EQ(memory[0x00b7], 0xf6);
  EXPECT_EQ(memory[0x1672], 0x21);
  EXPECT_EQ(memory[0x1673], 0xb7);
  EXPECT_EQ(memory[0x1674], 0xa2);
  EXPECT_EQ(memory[0xd414], 0x99);
}
TEST(CPU, instruction_BIT_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x24";

  constexpr std::uint16_t PC = 0x5f4b;
  constexpr uint8_t SP = 0x34;
  constexpr uint8_t A = 0x41;
  constexpr uint8_t X = 0x0f;
  constexpr uint8_t Y = 0xa2;
  constexpr uint8_t P = 0x66;

  memory[0x5f4b] = 0x24;
  memory[0x5f4c] = 0x3b;
  memory[0x5f4d] = 0x5b;
  memory[0x003b] = 0x4b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5f4d);
  EXPECT_EQ(cpu.get_SP(), 0x34);
  EXPECT_EQ(cpu.get_A(), 0x41);
  EXPECT_EQ(cpu.get_X(), 0x0f);
  EXPECT_EQ(cpu.get_Y(), 0xa2);
  EXPECT_EQ(cpu.get_P(), 0x64);

  EXPECT_EQ(memory[0x003b], 0x4b);
  EXPECT_EQ(memory[0x5f4b], 0x24);
  EXPECT_EQ(memory[0x5f4c], 0x3b);
  EXPECT_EQ(memory[0x5f4d], 0x5b);
}
TEST(CPU, instruction_AND_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xf0a2;
  constexpr uint8_t SP = 0x19;
  constexpr uint8_t A = 0x37;
  constexpr uint8_t X = 0xad;
  constexpr uint8_t Y = 0xb4;
  constexpr uint8_t P = 0xab;

  memory[0xf0a2] = 0x25;
  memory[0xf0a3] = 0xda;
  memory[0xf0a4] = 0x5a;
  memory[0x00da] = 0xfc;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xf0a4);
  EXPECT_EQ(cpu.get_SP(), 0x19);
  EXPECT_EQ(cpu.get_A(), 0x34);
  EXPECT_EQ(cpu.get_X(), 0xad);
  EXPECT_EQ(cpu.get_Y(), 0xb4);
  EXPECT_EQ(cpu.get_P(), 0x29);

  EXPECT_EQ(memory[0x00da], 0xfc);
  EXPECT_EQ(memory[0xf0a2], 0x25);
  EXPECT_EQ(memory[0xf0a3], 0xda);
  EXPECT_EQ(memory[0xf0a4], 0x5a);
}
TEST(CPU, instruction_ROL_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x26";

  constexpr std::uint16_t PC = 0x566a;
  constexpr uint8_t SP = 0x87;
  constexpr uint8_t A = 0x35;
  constexpr uint8_t X = 0xe7;
  constexpr uint8_t Y = 0x6d;
  constexpr uint8_t P = 0x2e;

  memory[0x566a] = 0x26;
  memory[0x566b] = 0x2c;
  memory[0x566c] = 0x39;
  memory[0x002c] = 0x8b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x566c);
  EXPECT_EQ(cpu.get_SP(), 0x87);
  EXPECT_EQ(cpu.get_A(), 0x35);
  EXPECT_EQ(cpu.get_X(), 0xe7);
  EXPECT_EQ(cpu.get_Y(), 0x6d);
  EXPECT_EQ(cpu.get_P(), 0x2d);

  EXPECT_EQ(memory[0x002c], 0x16);
  EXPECT_EQ(memory[0x566a], 0x26);
  EXPECT_EQ(memory[0x566b], 0x2c);
  EXPECT_EQ(memory[0x566c], 0x39);
}
TEST(CPU, instruction_PLP_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x28";

  constexpr std::uint16_t PC = 0xa532;
  constexpr uint8_t SP = 0xa3;
  constexpr uint8_t A = 0x9e;
  constexpr uint8_t X = 0x77;
  constexpr uint8_t Y = 0x6e;
  constexpr uint8_t P = 0xad;

  memory[0xa532] = 0x28;
  memory[0xa533] = 0xc6;
  memory[0xa534] = 0x97;
  memory[0x01a3] = 0x30;
  memory[0x01a4] = 0x94;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa533);
  EXPECT_EQ(cpu.get_SP(), 0xa4);
  EXPECT_EQ(cpu.get_A(), 0x9e);
  EXPECT_EQ(cpu.get_X(), 0x77);
  EXPECT_EQ(cpu.get_Y(), 0x6e);
  EXPECT_EQ(cpu.get_P(), 0xa4);

  EXPECT_EQ(memory[0x01a3], 0x30);
  EXPECT_EQ(memory[0x01a4], 0x94);
  EXPECT_EQ(memory[0xa532], 0x28);
  EXPECT_EQ(memory[0xa533], 0xc6);
  EXPECT_EQ(memory[0xa534], 0x97);
}
TEST(CPU, instruction_AND_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xa4c7;
  constexpr uint8_t SP = 0x1d;
  constexpr uint8_t A = 0xb0;
  constexpr uint8_t X = 0x88;
  constexpr uint8_t Y = 0x4b;
  constexpr uint8_t P = 0x22;

  memory[0xa4c7] = 0x29;
  memory[0xa4c8] = 0x14;
  memory[0xa4c9] = 0xc3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa4c9);
  EXPECT_EQ(cpu.get_SP(), 0x1d);
  EXPECT_EQ(cpu.get_A(), 0x10);
  EXPECT_EQ(cpu.get_X(), 0x88);
  EXPECT_EQ(cpu.get_Y(), 0x4b);
  EXPECT_EQ(cpu.get_P(), 0x20);

  EXPECT_EQ(memory[0xa4c7], 0x29);
  EXPECT_EQ(memory[0xa4c8], 0x14);
  EXPECT_EQ(memory[0xa4c9], 0xc3);
}
TEST(CPU, instruction_ROL_accumulator) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x2a";

  constexpr std::uint16_t PC = 0x525d;
  constexpr uint8_t SP = 0xba;
  constexpr uint8_t A = 0xaf;
  constexpr uint8_t X = 0xbe;
  constexpr uint8_t Y = 0xef;
  constexpr uint8_t P = 0xae;

  memory[0x525d] = 0x2a;
  memory[0x525e] = 0xd4;
  memory[0x525f] = 0xc3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x525e);
  EXPECT_EQ(cpu.get_SP(), 0xba);
  EXPECT_EQ(cpu.get_A(), 0x5e);
  EXPECT_EQ(cpu.get_X(), 0xbe);
  EXPECT_EQ(cpu.get_Y(), 0xef);
  EXPECT_EQ(cpu.get_P(), 0x2d);

  EXPECT_EQ(memory[0x525d], 0x2a);
  EXPECT_EQ(memory[0x525e], 0xd4);
  EXPECT_EQ(memory[0x525f], 0xc3);
}
TEST(CPU, instruction_BIT_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x2c";

  constexpr std::uint16_t PC = 0x2fc0;
  constexpr uint8_t SP = 0xf8;
  constexpr uint8_t A = 0x52;
  constexpr uint8_t X = 0x5b;
  constexpr uint8_t Y = 0x1f;
  constexpr uint8_t P = 0xa4;

  memory[0x2fc0] = 0x2c;
  memory[0x2fc1] = 0x9a;
  memory[0x2fc2] = 0xd2;
  memory[0xd29a] = 0xae;
  memory[0x2fc3] = 0x5d;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x2fc3);
  EXPECT_EQ(cpu.get_SP(), 0xf8);
  EXPECT_EQ(cpu.get_A(), 0x52);
  EXPECT_EQ(cpu.get_X(), 0x5b);
  EXPECT_EQ(cpu.get_Y(), 0x1f);
  EXPECT_EQ(cpu.get_P(), 0xa4);

  EXPECT_EQ(memory[0x2fc0], 0x2c);
  EXPECT_EQ(memory[0x2fc1], 0x9a);
  EXPECT_EQ(memory[0x2fc2], 0xd2);
  EXPECT_EQ(memory[0x2fc3], 0x5d);
  EXPECT_EQ(memory[0xd29a], 0xae);
}
TEST(CPU, instruction_AND_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x6279;
  constexpr uint8_t SP = 0xf1;
  constexpr uint8_t A = 0x77;
  constexpr uint8_t X = 0xc9;
  constexpr uint8_t Y = 0xe2;
  constexpr uint8_t P = 0x2d;

  memory[0x6279] = 0x2d;
  memory[0x627a] = 0x51;
  memory[0x627b] = 0x19;
  memory[0x1951] = 0x91;
  memory[0x627c] = 0xf7;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x627c);
  EXPECT_EQ(cpu.get_SP(), 0xf1);
  EXPECT_EQ(cpu.get_A(), 0x11);
  EXPECT_EQ(cpu.get_X(), 0xc9);
  EXPECT_EQ(cpu.get_Y(), 0xe2);
  EXPECT_EQ(cpu.get_P(), 0x2d);

  EXPECT_EQ(memory[0x1951], 0x91);
  EXPECT_EQ(memory[0x6279], 0x2d);
  EXPECT_EQ(memory[0x627a], 0x51);
  EXPECT_EQ(memory[0x627b], 0x19);
  EXPECT_EQ(memory[0x627c], 0xf7);
}
TEST(CPU, instruction_ROL_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x2e";

  constexpr std::uint16_t PC = 0xd3af;
  constexpr uint8_t SP = 0x55;
  constexpr uint8_t A = 0x3b;
  constexpr uint8_t X = 0x4a;
  constexpr uint8_t Y = 0x1c;
  constexpr uint8_t P = 0xe0;

  memory[0xd3af] = 0x2e;
  memory[0xd3b0] = 0x7c;
  memory[0xd3b1] = 0xca;
  memory[0xca7c] = 0x55;
  memory[0xd3b2] = 0xf3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd3b2);
  EXPECT_EQ(cpu.get_SP(), 0x55);
  EXPECT_EQ(cpu.get_A(), 0x3b);
  EXPECT_EQ(cpu.get_X(), 0x4a);
  EXPECT_EQ(cpu.get_Y(), 0x1c);
  EXPECT_EQ(cpu.get_P(), 0xe0);

  EXPECT_EQ(memory[0xca7c], 0xaa);
  EXPECT_EQ(memory[0xd3af], 0x2e);
  EXPECT_EQ(memory[0xd3b0], 0x7c);
  EXPECT_EQ(memory[0xd3b1], 0xca);
  EXPECT_EQ(memory[0xd3b2], 0xf3);
}
TEST(CPU, instruction_BMI_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x30";

  constexpr std::uint16_t PC = 0x5e13;
  constexpr uint8_t SP = 0x90;
  constexpr uint8_t A = 0x9c;
  constexpr uint8_t X = 0xc1;
  constexpr uint8_t Y = 0xbe;
  constexpr uint8_t P = 0x29;

  memory[0x5e13] = 0x30;
  memory[0x5e14] = 0x1d;
  memory[0x5e15] = 0x68;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5e15);
  EXPECT_EQ(cpu.get_SP(), 0x90);
  EXPECT_EQ(cpu.get_A(), 0x9c);
  EXPECT_EQ(cpu.get_X(), 0xc1);
  EXPECT_EQ(cpu.get_Y(), 0xbe);
  EXPECT_EQ(cpu.get_P(), 0x29);

  EXPECT_EQ(memory[0x5e13], 0x30);
  EXPECT_EQ(memory[0x5e14], 0x1d);
  EXPECT_EQ(memory[0x5e15], 0x68);
}
TEST(CPU, instruction_AND_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x5bc8;
  constexpr uint8_t SP = 0x4f;
  constexpr uint8_t A = 0x7d;
  constexpr uint8_t X = 0xd2;
  constexpr uint8_t Y = 0x5f;
  constexpr uint8_t P = 0xae;

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
  EXPECT_EQ(cpu.get_A(), 0x6d);
  EXPECT_EQ(cpu.get_X(), 0xd2);
  EXPECT_EQ(cpu.get_Y(), 0x5f);
  EXPECT_EQ(cpu.get_P(), 0x2c);

  EXPECT_EQ(memory[0x00d3], 0x5c);
  EXPECT_EQ(memory[0x00d4], 0x09);
  EXPECT_EQ(memory[0x09bb], 0x6d);
  EXPECT_EQ(memory[0x5bc8], 0x31);
  EXPECT_EQ(memory[0x5bc9], 0xd3);
  EXPECT_EQ(memory[0x5bca], 0x21);
}
TEST(CPU, instruction_AND_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xf4be;
  constexpr uint8_t SP = 0xbf;
  constexpr uint8_t A = 0x83;
  constexpr uint8_t X = 0xa3;
  constexpr uint8_t Y = 0xbc;
  constexpr uint8_t P = 0xa3;

  memory[0xf4be] = 0x35;
  memory[0xf4bf] = 0x0c;
  memory[0xf4c0] = 0xdc;
  memory[0x000c] = 0x38;
  memory[0x00af] = 0xf6;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xf4c0);
  EXPECT_EQ(cpu.get_SP(), 0xbf);
  EXPECT_EQ(cpu.get_A(), 0x82);
  EXPECT_EQ(cpu.get_X(), 0xa3);
  EXPECT_EQ(cpu.get_Y(), 0xbc);
  EXPECT_EQ(cpu.get_P(), 0xa1);

  EXPECT_EQ(memory[0x000c], 0x38);
  EXPECT_EQ(memory[0x00af], 0xf6);
  EXPECT_EQ(memory[0xf4be], 0x35);
  EXPECT_EQ(memory[0xf4bf], 0x0c);
  EXPECT_EQ(memory[0xf4c0], 0xdc);
}
TEST(CPU, instruction_ROL_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x36";

  constexpr std::uint16_t PC = 0x3d0d;
  constexpr uint8_t SP = 0x16;
  constexpr uint8_t A = 0x19;
  constexpr uint8_t X = 0x67;
  constexpr uint8_t Y = 0x59;
  constexpr uint8_t P = 0xe9;

  memory[0x3d0d] = 0x36;
  memory[0x3d0e] = 0x13;
  memory[0x3d0f] = 0x1b;
  memory[0x0013] = 0xd8;
  memory[0x007a] = 0x2d;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x3d0f);
  EXPECT_EQ(cpu.get_SP(), 0x16);
  EXPECT_EQ(cpu.get_A(), 0x19);
  EXPECT_EQ(cpu.get_X(), 0x67);
  EXPECT_EQ(cpu.get_Y(), 0x59);
  EXPECT_EQ(cpu.get_P(), 0x68);

  EXPECT_EQ(memory[0x0013], 0xd8);
  EXPECT_EQ(memory[0x007a], 0x5b);
  EXPECT_EQ(memory[0x3d0d], 0x36);
  EXPECT_EQ(memory[0x3d0e], 0x13);
  EXPECT_EQ(memory[0x3d0f], 0x1b);
}
TEST(CPU, instruction_SEC_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x38";

  constexpr std::uint16_t PC = 0x85d6;
  constexpr uint8_t SP = 0x43;
  constexpr uint8_t A = 0xa8;
  constexpr uint8_t X = 0xd2;
  constexpr uint8_t Y = 0xb7;
  constexpr uint8_t P = 0xe1;

  memory[0x85d6] = 0x38;
  memory[0x85d7] = 0x08;
  memory[0x85d8] = 0x67;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x85d7);
  EXPECT_EQ(cpu.get_SP(), 0x43);
  EXPECT_EQ(cpu.get_A(), 0xa8);
  EXPECT_EQ(cpu.get_X(), 0xd2);
  EXPECT_EQ(cpu.get_Y(), 0xb7);
  EXPECT_EQ(cpu.get_P(), 0xe1);

  EXPECT_EQ(memory[0x85d6], 0x38);
  EXPECT_EQ(memory[0x85d7], 0x08);
  EXPECT_EQ(memory[0x85d8], 0x67);
}
TEST(CPU, instruction_AND_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xe59a;
  constexpr uint8_t SP = 0xc8;
  constexpr uint8_t A = 0x91;
  constexpr uint8_t X = 0x4d;
  constexpr uint8_t Y = 0x80;
  constexpr uint8_t P = 0xa2;

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
  EXPECT_EQ(cpu.get_A(), 0x81);
  EXPECT_EQ(cpu.get_X(), 0x4d);
  EXPECT_EQ(cpu.get_Y(), 0x80);
  EXPECT_EQ(cpu.get_P(), 0xa0);

  EXPECT_EQ(memory[0xe59a], 0x39);
  EXPECT_EQ(memory[0xe59b], 0x94);
  EXPECT_EQ(memory[0xe59c], 0xf0);
  EXPECT_EQ(memory[0xe59d], 0x98);
  EXPECT_EQ(memory[0xf014], 0x23);
  EXPECT_EQ(memory[0xf114], 0xe5);
}
TEST(CPU, instruction_AND_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xaaac;
  constexpr uint8_t SP = 0x0e;
  constexpr uint8_t A = 0x3a;
  constexpr uint8_t X = 0xdf;
  constexpr uint8_t Y = 0x94;
  constexpr uint8_t P = 0x6b;

  memory[0xaaac] = 0x3d;
  memory[0xaaad] = 0x20;
  memory[0xaaae] = 0x00;
  memory[0x00ff] = 0x44;
  memory[0xaaaf] = 0x45;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xaaaf);
  EXPECT_EQ(cpu.get_SP(), 0x0e);
  EXPECT_EQ(cpu.get_A(), 0x00);
  EXPECT_EQ(cpu.get_X(), 0xdf);
  EXPECT_EQ(cpu.get_Y(), 0x94);
  EXPECT_EQ(cpu.get_P(), 0x6b);

  EXPECT_EQ(memory[0x00ff], 0x44);
  EXPECT_EQ(memory[0xaaac], 0x3d);
  EXPECT_EQ(memory[0xaaad], 0x20);
  EXPECT_EQ(memory[0xaaae], 0x00);
  EXPECT_EQ(memory[0xaaaf], 0x45);
}
TEST(CPU, instruction_ROL_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x3e";

  constexpr std::uint16_t PC = 0x6c7a;
  constexpr uint8_t SP = 0x78;
  constexpr uint8_t A = 0xc9;
  constexpr uint8_t X = 0x48;
  constexpr uint8_t Y = 0x25;
  constexpr uint8_t P = 0x6c;

  memory[0x6c7a] = 0x3e;
  memory[0x6c7b] = 0x55;
  memory[0x6c7c] = 0x5a;
  memory[0x5a9d] = 0xf6;
  memory[0x6c7d] = 0x2b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x6c7d);
  EXPECT_EQ(cpu.get_SP(), 0x78);
  EXPECT_EQ(cpu.get_A(), 0xc9);
  EXPECT_EQ(cpu.get_X(), 0x48);
  EXPECT_EQ(cpu.get_Y(), 0x25);
  EXPECT_EQ(cpu.get_P(), 0xed);

  EXPECT_EQ(memory[0x5a9d], 0xec);
  EXPECT_EQ(memory[0x6c7a], 0x3e);
  EXPECT_EQ(memory[0x6c7b], 0x55);
  EXPECT_EQ(memory[0x6c7c], 0x5a);
  EXPECT_EQ(memory[0x6c7d], 0x2b);
}
TEST(CPU, instruction_RTI_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x40";

  constexpr std::uint16_t PC = 0x8771;
  constexpr uint8_t SP = 0x6e;
  constexpr uint8_t A = 0xa2;
  constexpr uint8_t X = 0x81;
  constexpr uint8_t Y = 0x7e;
  constexpr uint8_t P = 0x63;

  memory[0x8771] = 0x40;
  memory[0x8772] = 0x9c;
  memory[0x8773] = 0x2c;
  memory[0x016e] = 0x98;
  memory[0x016f] = 0x9c;
  memory[0x0170] = 0xaa;
  memory[0x0171] = 0x65;
  memory[0x65aa] = 0x0e;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x65aa);
  EXPECT_EQ(cpu.get_SP(), 0x71);
  EXPECT_EQ(cpu.get_A(), 0xa2);
  EXPECT_EQ(cpu.get_X(), 0x81);
  EXPECT_EQ(cpu.get_Y(), 0x7e);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x016e], 0x98);
  EXPECT_EQ(memory[0x016f], 0x9c);
  EXPECT_EQ(memory[0x0170], 0xaa);
  EXPECT_EQ(memory[0x0171], 0x65);
  EXPECT_EQ(memory[0x65aa], 0x0e);
  EXPECT_EQ(memory[0x8771], 0x40);
  EXPECT_EQ(memory[0x8772], 0x9c);
  EXPECT_EQ(memory[0x8773], 0x2c);
}
TEST(CPU, instruction_EOR_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x02b6;
  constexpr uint8_t SP = 0xbb;
  constexpr uint8_t A = 0x22;
  constexpr uint8_t X = 0x2e;
  constexpr uint8_t Y = 0x10;
  constexpr uint8_t P = 0x27;

  memory[0x02b6] = 0x41;
  memory[0x02b7] = 0x85;
  memory[0x02b8] = 0x36;
  memory[0x0085] = 0x1e;
  memory[0x00b3] = 0xa1;
  memory[0x00b4] = 0x56;
  memory[0x56a1] = 0xd3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x02b8);
  EXPECT_EQ(cpu.get_SP(), 0xbb);
  EXPECT_EQ(cpu.get_A(), 0xf1);
  EXPECT_EQ(cpu.get_X(), 0x2e);
  EXPECT_EQ(cpu.get_Y(), 0x10);
  EXPECT_EQ(cpu.get_P(), 0xa5);

  EXPECT_EQ(memory[0x0085], 0x1e);
  EXPECT_EQ(memory[0x00b3], 0xa1);
  EXPECT_EQ(memory[0x00b4], 0x56);
  EXPECT_EQ(memory[0x02b6], 0x41);
  EXPECT_EQ(memory[0x02b7], 0x85);
  EXPECT_EQ(memory[0x02b8], 0x36);
  EXPECT_EQ(memory[0x56a1], 0xd3);
}
TEST(CPU, instruction_EOR_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xa082;
  constexpr uint8_t SP = 0x7e;
  constexpr uint8_t A = 0x81;
  constexpr uint8_t X = 0x50;
  constexpr uint8_t Y = 0xf3;
  constexpr uint8_t P = 0x60;

  memory[0xa082] = 0x45;
  memory[0xa083] = 0x0e;
  memory[0xa084] = 0x16;
  memory[0x000e] = 0xc7;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa084);
  EXPECT_EQ(cpu.get_SP(), 0x7e);
  EXPECT_EQ(cpu.get_A(), 0x46);
  EXPECT_EQ(cpu.get_X(), 0x50);
  EXPECT_EQ(cpu.get_Y(), 0xf3);
  EXPECT_EQ(cpu.get_P(), 0x60);

  EXPECT_EQ(memory[0x000e], 0xc7);
  EXPECT_EQ(memory[0xa082], 0x45);
  EXPECT_EQ(memory[0xa083], 0x0e);
  EXPECT_EQ(memory[0xa084], 0x16);
}
TEST(CPU, instruction_LSR_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x46";

  constexpr std::uint16_t PC = 0xcce2;
  constexpr uint8_t SP = 0xfb;
  constexpr uint8_t A = 0x8c;
  constexpr uint8_t X = 0x20;
  constexpr uint8_t Y = 0xaf;
  constexpr uint8_t P = 0x23;

  memory[0xcce2] = 0x46;
  memory[0xcce3] = 0xe3;
  memory[0xcce4] = 0xed;
  memory[0x00e3] = 0x85;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xcce4);
  EXPECT_EQ(cpu.get_SP(), 0xfb);
  EXPECT_EQ(cpu.get_A(), 0x8c);
  EXPECT_EQ(cpu.get_X(), 0x20);
  EXPECT_EQ(cpu.get_Y(), 0xaf);
  EXPECT_EQ(cpu.get_P(), 0x21);

  EXPECT_EQ(memory[0x00e3], 0x42);
  EXPECT_EQ(memory[0xcce2], 0x46);
  EXPECT_EQ(memory[0xcce3], 0xe3);
  EXPECT_EQ(memory[0xcce4], 0xed);
}
TEST(CPU, instruction_PHA_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x48";

  constexpr std::uint16_t PC = 0x5063;
  constexpr uint8_t SP = 0x9f;
  constexpr uint8_t A = 0x3e;
  constexpr uint8_t X = 0x33;
  constexpr uint8_t Y = 0x4e;
  constexpr uint8_t P = 0xac;

  memory[0x5063] = 0x48;
  memory[0x5064] = 0xe0;
  memory[0x5065] = 0x36;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5064);
  EXPECT_EQ(cpu.get_SP(), 0x9e);
  EXPECT_EQ(cpu.get_A(), 0x3e);
  EXPECT_EQ(cpu.get_X(), 0x33);
  EXPECT_EQ(cpu.get_Y(), 0x4e);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x019f], 0x3e);
  EXPECT_EQ(memory[0x5063], 0x48);
  EXPECT_EQ(memory[0x5064], 0xe0);
  EXPECT_EQ(memory[0x5065], 0x36);
}
TEST(CPU, instruction_EOR_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x67c5;
  constexpr uint8_t SP = 0x63;
  constexpr uint8_t A = 0x22;
  constexpr uint8_t X = 0xf2;
  constexpr uint8_t Y = 0x47;
  constexpr uint8_t P = 0xab;

  memory[0x67c5] = 0x49;
  memory[0x67c6] = 0x9d;
  memory[0x67c7] = 0x64;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x67c7);
  EXPECT_EQ(cpu.get_SP(), 0x63);
  EXPECT_EQ(cpu.get_A(), 0xbf);
  EXPECT_EQ(cpu.get_X(), 0xf2);
  EXPECT_EQ(cpu.get_Y(), 0x47);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x67c5], 0x49);
  EXPECT_EQ(memory[0x67c6], 0x9d);
  EXPECT_EQ(memory[0x67c7], 0x64);
}
TEST(CPU, instruction_LSR_accumulator) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x4a";

  constexpr std::uint16_t PC = 0x1280;
  constexpr uint8_t SP = 0xb6;
  constexpr uint8_t A = 0xf3;
  constexpr uint8_t X = 0xbc;
  constexpr uint8_t Y = 0x48;
  constexpr uint8_t P = 0x2b;

  memory[0x1280] = 0x4a;
  memory[0x1281] = 0x10;
  memory[0x1282] = 0x20;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x1281);
  EXPECT_EQ(cpu.get_SP(), 0xb6);
  EXPECT_EQ(cpu.get_A(), 0x79);
  EXPECT_EQ(cpu.get_X(), 0xbc);
  EXPECT_EQ(cpu.get_Y(), 0x48);
  EXPECT_EQ(cpu.get_P(), 0x29);

  EXPECT_EQ(memory[0x1280], 0x4a);
  EXPECT_EQ(memory[0x1281], 0x10);
  EXPECT_EQ(memory[0x1282], 0x20);
}
TEST(CPU, instruction_JMP_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x4c";

  constexpr std::uint16_t PC = 0x1be6;
  constexpr uint8_t SP = 0x9f;
  constexpr uint8_t A = 0xcf;
  constexpr uint8_t X = 0x27;
  constexpr uint8_t Y = 0x02;
  constexpr uint8_t P = 0x68;

  memory[0x1be6] = 0x4c;
  memory[0x1be7] = 0xf8;
  memory[0x1be8] = 0xce;
  memory[0xcef8] = 0xab;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xcef8);
  EXPECT_EQ(cpu.get_SP(), 0x9f);
  EXPECT_EQ(cpu.get_A(), 0xcf);
  EXPECT_EQ(cpu.get_X(), 0x27);
  EXPECT_EQ(cpu.get_Y(), 0x02);
  EXPECT_EQ(cpu.get_P(), 0x68);

  EXPECT_EQ(memory[0x1be6], 0x4c);
  EXPECT_EQ(memory[0x1be7], 0xf8);
  EXPECT_EQ(memory[0x1be8], 0xce);
  EXPECT_EQ(memory[0xcef8], 0xab);
}
TEST(CPU, instruction_EOR_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x0f5a;
  constexpr uint8_t SP = 0xaa;
  constexpr uint8_t A = 0x16;
  constexpr uint8_t X = 0x52;
  constexpr uint8_t Y = 0xce;
  constexpr uint8_t P = 0xa2;

  memory[0x0f5a] = 0x4d;
  memory[0x0f5b] = 0x1a;
  memory[0x0f5c] = 0x0b;
  memory[0x0b1a] = 0x1f;
  memory[0x0f5d] = 0x69;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0f5d);
  EXPECT_EQ(cpu.get_SP(), 0xaa);
  EXPECT_EQ(cpu.get_A(), 0x09);
  EXPECT_EQ(cpu.get_X(), 0x52);
  EXPECT_EQ(cpu.get_Y(), 0xce);
  EXPECT_EQ(cpu.get_P(), 0x20);

  EXPECT_EQ(memory[0x0b1a], 0x1f);
  EXPECT_EQ(memory[0x0f5a], 0x4d);
  EXPECT_EQ(memory[0x0f5b], 0x1a);
  EXPECT_EQ(memory[0x0f5c], 0x0b);
  EXPECT_EQ(memory[0x0f5d], 0x69);
}
TEST(CPU, instruction_LSR_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x4e";

  constexpr std::uint16_t PC = 0xfcfe;
  constexpr uint8_t SP = 0xc6;
  constexpr uint8_t A = 0x7f;
  constexpr uint8_t X = 0xf4;
  constexpr uint8_t Y = 0xc6;
  constexpr uint8_t P = 0x2f;

  memory[0xfcfe] = 0x4e;
  memory[0xfcff] = 0x58;
  memory[0xfd00] = 0xa8;
  memory[0xa858] = 0xc0;
  memory[0xfd01] = 0x58;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xfd01);
  EXPECT_EQ(cpu.get_SP(), 0xc6);
  EXPECT_EQ(cpu.get_A(), 0x7f);
  EXPECT_EQ(cpu.get_X(), 0xf4);
  EXPECT_EQ(cpu.get_Y(), 0xc6);
  EXPECT_EQ(cpu.get_P(), 0x2c);

  EXPECT_EQ(memory[0xa858], 0x60);
  EXPECT_EQ(memory[0xfcfe], 0x4e);
  EXPECT_EQ(memory[0xfcff], 0x58);
  EXPECT_EQ(memory[0xfd00], 0xa8);
  EXPECT_EQ(memory[0xfd01], 0x58);
}
TEST(CPU, instruction_BVC_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x50";

  constexpr std::uint16_t PC = 0xaca3;
  constexpr uint8_t SP = 0xe2;
  constexpr uint8_t A = 0x47;
  constexpr uint8_t X = 0x28;
  constexpr uint8_t Y = 0x5f;
  constexpr uint8_t P = 0xe8;

  memory[0xaca3] = 0x50;
  memory[0xaca4] = 0x59;
  memory[0xaca5] = 0xa3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xaca5);
  EXPECT_EQ(cpu.get_SP(), 0xe2);
  EXPECT_EQ(cpu.get_A(), 0x47);
  EXPECT_EQ(cpu.get_X(), 0x28);
  EXPECT_EQ(cpu.get_Y(), 0x5f);
  EXPECT_EQ(cpu.get_P(), 0xe8);

  EXPECT_EQ(memory[0xaca3], 0x50);
  EXPECT_EQ(memory[0xaca4], 0x59);
  EXPECT_EQ(memory[0xaca5], 0xa3);
}
TEST(CPU, instruction_EOR_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x4a29;
  constexpr uint8_t SP = 0xe7;
  constexpr uint8_t A = 0x9a;
  constexpr uint8_t X = 0x4a;
  constexpr uint8_t Y = 0x57;
  constexpr uint8_t P = 0xef;

  memory[0x4a29] = 0x51;
  memory[0x4a2a] = 0xc4;
  memory[0x4a2b] = 0x38;
  memory[0x00c4] = 0xdf;
  memory[0x00c5] = 0x91;
  memory[0x9136] = 0xf9;
  memory[0x9236] = 0x41;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4a2b);
  EXPECT_EQ(cpu.get_SP(), 0xe7);
  EXPECT_EQ(cpu.get_A(), 0xdb);
  EXPECT_EQ(cpu.get_X(), 0x4a);
  EXPECT_EQ(cpu.get_Y(), 0x57);
  EXPECT_EQ(cpu.get_P(), 0xed);

  EXPECT_EQ(memory[0x00c4], 0xdf);
  EXPECT_EQ(memory[0x00c5], 0x91);
  EXPECT_EQ(memory[0x4a29], 0x51);
  EXPECT_EQ(memory[0x4a2a], 0xc4);
  EXPECT_EQ(memory[0x4a2b], 0x38);
  EXPECT_EQ(memory[0x9136], 0xf9);
  EXPECT_EQ(memory[0x9236], 0x41);
}
TEST(CPU, instruction_EOR_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xd958;
  constexpr uint8_t SP = 0x7e;
  constexpr uint8_t A = 0x5c;
  constexpr uint8_t X = 0x18;
  constexpr uint8_t Y = 0xcf;
  constexpr uint8_t P = 0x2a;

  memory[0xd958] = 0x55;
  memory[0xd959] = 0x7f;
  memory[0xd95a] = 0x54;
  memory[0x007f] = 0xa8;
  memory[0x0097] = 0x09;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd95a);
  EXPECT_EQ(cpu.get_SP(), 0x7e);
  EXPECT_EQ(cpu.get_A(), 0x55);
  EXPECT_EQ(cpu.get_X(), 0x18);
  EXPECT_EQ(cpu.get_Y(), 0xcf);
  EXPECT_EQ(cpu.get_P(), 0x28);

  EXPECT_EQ(memory[0x007f], 0xa8);
  EXPECT_EQ(memory[0x0097], 0x09);
  EXPECT_EQ(memory[0xd958], 0x55);
  EXPECT_EQ(memory[0xd959], 0x7f);
  EXPECT_EQ(memory[0xd95a], 0x54);
}
TEST(CPU, instruction_LSR_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x56";

  constexpr std::uint16_t PC = 0x44cc;
  constexpr uint8_t SP = 0xb7;
  constexpr uint8_t A = 0x25;
  constexpr uint8_t X = 0x5e;
  constexpr uint8_t Y = 0xd0;
  constexpr uint8_t P = 0x2b;

  memory[0x44cc] = 0x56;
  memory[0x44cd] = 0xad;
  memory[0x44ce] = 0xc9;
  memory[0x00ad] = 0x73;
  memory[0x000b] = 0xff;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x44ce);
  EXPECT_EQ(cpu.get_SP(), 0xb7);
  EXPECT_EQ(cpu.get_A(), 0x25);
  EXPECT_EQ(cpu.get_X(), 0x5e);
  EXPECT_EQ(cpu.get_Y(), 0xd0);
  EXPECT_EQ(cpu.get_P(), 0x29);

  EXPECT_EQ(memory[0x000b], 0x7f);
  EXPECT_EQ(memory[0x00ad], 0x73);
  EXPECT_EQ(memory[0x44cc], 0x56);
  EXPECT_EQ(memory[0x44cd], 0xad);
  EXPECT_EQ(memory[0x44ce], 0xc9);
}
TEST(CPU, instruction_CLI_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x58";

  constexpr std::uint16_t PC = 0x448a;
  constexpr uint8_t SP = 0xf5;
  constexpr uint8_t A = 0xb6;
  constexpr uint8_t X = 0xd3;
  constexpr uint8_t Y = 0x96;
  constexpr uint8_t P = 0xa9;

  memory[0x448a] = 0x58;
  memory[0x448b] = 0x71;
  memory[0x448c] = 0xbb;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x448b);
  EXPECT_EQ(cpu.get_SP(), 0xf5);
  EXPECT_EQ(cpu.get_A(), 0xb6);
  EXPECT_EQ(cpu.get_X(), 0xd3);
  EXPECT_EQ(cpu.get_Y(), 0x96);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x448a], 0x58);
  EXPECT_EQ(memory[0x448b], 0x71);
  EXPECT_EQ(memory[0x448c], 0xbb);
}
TEST(CPU, instruction_EOR_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0x084a;
  constexpr uint8_t SP = 0x49;
  constexpr uint8_t A = 0xf4;
  constexpr uint8_t X = 0xe3;
  constexpr uint8_t Y = 0x5d;
  constexpr uint8_t P = 0x2d;

  memory[0x084a] = 0x59;
  memory[0x084b] = 0x66;
  memory[0x084c] = 0x8f;
  memory[0x8fc3] = 0xb9;
  memory[0x084d] = 0xa2;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x084d);
  EXPECT_EQ(cpu.get_SP(), 0x49);
  EXPECT_EQ(cpu.get_A(), 0x4d);
  EXPECT_EQ(cpu.get_X(), 0xe3);
  EXPECT_EQ(cpu.get_Y(), 0x5d);
  EXPECT_EQ(cpu.get_P(), 0x2d);

  EXPECT_EQ(memory[0x084a], 0x59);
  EXPECT_EQ(memory[0x084b], 0x66);
  EXPECT_EQ(memory[0x084c], 0x8f);
  EXPECT_EQ(memory[0x084d], 0xa2);
  EXPECT_EQ(memory[0x8fc3], 0xb9);
}
TEST(CPU, instruction_EOR_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};

  constexpr std::uint16_t PC = 0xd663;
  constexpr uint8_t SP = 0x43;
  constexpr uint8_t A = 0x54;
  constexpr uint8_t X = 0x16;
  constexpr uint8_t Y = 0x27;
  constexpr uint8_t P = 0xe1;

  memory[0xd663] = 0x5d;
  memory[0xd664] = 0xf7;
  memory[0xd665] = 0xec;
  memory[0xec0d] = 0x76;
  memory[0xed0d] = 0x79;
  memory[0xd666] = 0x7c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd666);
  EXPECT_EQ(cpu.get_SP(), 0x43);
  EXPECT_EQ(cpu.get_A(), 0x2d);
  EXPECT_EQ(cpu.get_X(), 0x16);
  EXPECT_EQ(cpu.get_Y(), 0x27);
  EXPECT_EQ(cpu.get_P(), 0x61);

  EXPECT_EQ(memory[0xd663], 0x5d);
  EXPECT_EQ(memory[0xd664], 0xf7);
  EXPECT_EQ(memory[0xd665], 0xec);
  EXPECT_EQ(memory[0xd666], 0x7c);
  EXPECT_EQ(memory[0xec0d], 0x76);
  EXPECT_EQ(memory[0xed0d], 0x79);
}
TEST(CPU, instruction_LSR_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x5e";

  constexpr std::uint16_t PC = 0xc043;
  constexpr uint8_t SP = 0xf8;
  constexpr uint8_t A = 0xab;
  constexpr uint8_t X = 0x9e;
  constexpr uint8_t Y = 0xfc;
  constexpr uint8_t P = 0x28;

  memory[0xc043] = 0x5e;
  memory[0xc044] = 0x96;
  memory[0xc045] = 0x9e;
  memory[0x9e34] = 0x4a;
  memory[0x9f34] = 0xf4;
  memory[0xc046] = 0xa8;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xc046);
  EXPECT_EQ(cpu.get_SP(), 0xf8);
  EXPECT_EQ(cpu.get_A(), 0xab);
  EXPECT_EQ(cpu.get_X(), 0x9e);
  EXPECT_EQ(cpu.get_Y(), 0xfc);
  EXPECT_EQ(cpu.get_P(), 0x28);

  EXPECT_EQ(memory[0x9e34], 0x4a);
  EXPECT_EQ(memory[0x9f34], 0x7a);
  EXPECT_EQ(memory[0xc043], 0x5e);
  EXPECT_EQ(memory[0xc044], 0x96);
  EXPECT_EQ(memory[0xc045], 0x9e);
  EXPECT_EQ(memory[0xc046], 0xa8);
}
TEST(CPU, instruction_RTS_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x60";

  constexpr std::uint16_t PC = 0x4147;
  constexpr uint8_t SP = 0xcb;
  constexpr uint8_t A = 0xe7;
  constexpr uint8_t X = 0x14;
  constexpr uint8_t Y = 0x64;
  constexpr uint8_t P = 0xa6;

  memory[0x4147] = 0x60;
  memory[0x4148] = 0x14;
  memory[0x4149] = 0xe2;
  memory[0x01cb] = 0x98;
  memory[0x01cc] = 0xdc;
  memory[0x01cd] = 0x1d;
  memory[0x1ddc] = 0x5d;
  memory[0x1ddd] = 0xda;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x1ddd);
  EXPECT_EQ(cpu.get_SP(), 0xcd);
  EXPECT_EQ(cpu.get_A(), 0xe7);
  EXPECT_EQ(cpu.get_X(), 0x14);
  EXPECT_EQ(cpu.get_Y(), 0x64);
  EXPECT_EQ(cpu.get_P(), 0xa6);

  EXPECT_EQ(memory[0x01cb], 0x98);
  EXPECT_EQ(memory[0x01cc], 0xdc);
  EXPECT_EQ(memory[0x01cd], 0x1d);
  EXPECT_EQ(memory[0x1ddc], 0x5d);
  EXPECT_EQ(memory[0x1ddd], 0xda);
  EXPECT_EQ(memory[0x4147], 0x60);
  EXPECT_EQ(memory[0x4148], 0x14);
  EXPECT_EQ(memory[0x4149], 0xe2);
}
TEST(CPU, instruction_ADC_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x61";

  constexpr std::uint16_t PC = 0x406f;
  constexpr uint8_t SP = 0xfd;
  constexpr uint8_t A = 0x28;
  constexpr uint8_t X = 0x93;
  constexpr uint8_t Y = 0x85;
  constexpr uint8_t P = 0x64;

  memory[0x406f] = 0x61;
  memory[0x4070] = 0x96;
  memory[0x4071] = 0x69;
  memory[0x0096] = 0x80;
  memory[0x0029] = 0x3b;
  memory[0x002a] = 0x72;
  memory[0x723b] = 0x13;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4071);
  EXPECT_EQ(cpu.get_SP(), 0xfd);
  EXPECT_EQ(cpu.get_A(), 0x3b);
  EXPECT_EQ(cpu.get_X(), 0x93);
  EXPECT_EQ(cpu.get_Y(), 0x85);
  EXPECT_EQ(cpu.get_P(), 0x24);

  EXPECT_EQ(memory[0x0029], 0x3b);
  EXPECT_EQ(memory[0x002a], 0x72);
  EXPECT_EQ(memory[0x0096], 0x80);
  EXPECT_EQ(memory[0x406f], 0x61);
  EXPECT_EQ(memory[0x4070], 0x96);
  EXPECT_EQ(memory[0x4071], 0x69);
  EXPECT_EQ(memory[0x723b], 0x13);
}
TEST(CPU, instruction_ADC_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x65";

  constexpr std::uint16_t PC = 0x0231;
  constexpr uint8_t SP = 0x41;
  constexpr uint8_t A = 0x34;
  constexpr uint8_t X = 0xaa;
  constexpr uint8_t Y = 0x43;
  constexpr uint8_t P = 0x2b;

  memory[0x0231] = 0x65;
  memory[0x0232] = 0xcb;
  memory[0x0233] = 0x0c;
  memory[0x00cb] = 0xeb;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0233);
  EXPECT_EQ(cpu.get_SP(), 0x41);
  EXPECT_EQ(cpu.get_A(), 0x86);
  EXPECT_EQ(cpu.get_X(), 0xaa);
  EXPECT_EQ(cpu.get_Y(), 0x43);
  EXPECT_EQ(cpu.get_P(), 0x29);

  EXPECT_EQ(memory[0x00cb], 0xeb);
  EXPECT_EQ(memory[0x0231], 0x65);
  EXPECT_EQ(memory[0x0232], 0xcb);
  EXPECT_EQ(memory[0x0233], 0x0c);
}
TEST(CPU, instruction_ROR_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x66";

  constexpr std::uint16_t PC = 0x8c07;
  constexpr uint8_t SP = 0x9b;
  constexpr uint8_t A = 0x44;
  constexpr uint8_t X = 0x8e;
  constexpr uint8_t Y = 0xa4;
  constexpr uint8_t P = 0xaa;

  memory[0x8c07] = 0x66;
  memory[0x8c08] = 0x5d;
  memory[0x8c09] = 0x0c;
  memory[0x005d] = 0x9c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x8c09);
  EXPECT_EQ(cpu.get_SP(), 0x9b);
  EXPECT_EQ(cpu.get_A(), 0x44);
  EXPECT_EQ(cpu.get_X(), 0x8e);
  EXPECT_EQ(cpu.get_Y(), 0xa4);
  EXPECT_EQ(cpu.get_P(), 0x28);

  EXPECT_EQ(memory[0x005d], 0x4e);
  EXPECT_EQ(memory[0x8c07], 0x66);
  EXPECT_EQ(memory[0x8c08], 0x5d);
  EXPECT_EQ(memory[0x8c09], 0x0c);
}
TEST(CPU, instruction_PLA_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x68";

  constexpr std::uint16_t PC = 0x3021;
  constexpr uint8_t SP = 0xa4;
  constexpr uint8_t A = 0x32;
  constexpr uint8_t X = 0xb2;
  constexpr uint8_t Y = 0x4a;
  constexpr uint8_t P = 0x2e;

  memory[0x3021] = 0x68;
  memory[0x3022] = 0xb4;
  memory[0x3023] = 0x82;
  memory[0x01a4] = 0xe0;
  memory[0x01a5] = 0x36;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x3022);
  EXPECT_EQ(cpu.get_SP(), 0xa5);
  EXPECT_EQ(cpu.get_A(), 0x36);
  EXPECT_EQ(cpu.get_X(), 0xb2);
  EXPECT_EQ(cpu.get_Y(), 0x4a);
  EXPECT_EQ(cpu.get_P(), 0x2c);

  EXPECT_EQ(memory[0x01a4], 0xe0);
  EXPECT_EQ(memory[0x01a5], 0x36);
  EXPECT_EQ(memory[0x3021], 0x68);
  EXPECT_EQ(memory[0x3022], 0xb4);
  EXPECT_EQ(memory[0x3023], 0x82);
}
TEST(CPU, instruction_ADC_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x69";

  constexpr std::uint16_t PC = 0xbfdf;
  constexpr uint8_t SP = 0x2e;
  constexpr uint8_t A = 0x4c;
  constexpr uint8_t X = 0x24;
  constexpr uint8_t Y = 0x04;
  constexpr uint8_t P = 0xe4;

  memory[0xbfdf] = 0x69;
  memory[0xbfe0] = 0x1b;
  memory[0xbfe1] = 0x91;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xbfe1);
  EXPECT_EQ(cpu.get_SP(), 0x2e);
  EXPECT_EQ(cpu.get_A(), 0x67);
  EXPECT_EQ(cpu.get_X(), 0x24);
  EXPECT_EQ(cpu.get_Y(), 0x04);
  EXPECT_EQ(cpu.get_P(), 0x24);

  EXPECT_EQ(memory[0xbfdf], 0x69);
  EXPECT_EQ(memory[0xbfe0], 0x1b);
  EXPECT_EQ(memory[0xbfe1], 0x91);
}
TEST(CPU, instruction_ROR_accumulator) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x6a";

  constexpr std::uint16_t PC = 0xc7b0;
  constexpr uint8_t SP = 0x70;
  constexpr uint8_t A = 0x05;
  constexpr uint8_t X = 0xae;
  constexpr uint8_t Y = 0xf7;
  constexpr uint8_t P = 0x20;

  memory[0xc7b0] = 0x6a;
  memory[0xc7b1] = 0xfc;
  memory[0xc7b2] = 0x0f;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xc7b1);
  EXPECT_EQ(cpu.get_SP(), 0x70);
  EXPECT_EQ(cpu.get_A(), 0x02);
  EXPECT_EQ(cpu.get_X(), 0xae);
  EXPECT_EQ(cpu.get_Y(), 0xf7);
  EXPECT_EQ(cpu.get_P(), 0x21);

  EXPECT_EQ(memory[0xc7b0], 0x6a);
  EXPECT_EQ(memory[0xc7b1], 0xfc);
  EXPECT_EQ(memory[0xc7b2], 0x0f);
}
TEST(CPU, instruction_JMP_indirect) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x6c";

  constexpr std::uint16_t PC = 0xfb8f;
  constexpr uint8_t SP = 0x7b;
  constexpr uint8_t A = 0x19;
  constexpr uint8_t X = 0xc2;
  constexpr uint8_t Y = 0x03;
  constexpr uint8_t P = 0xef;

  memory[0xfb8f] = 0x6c;
  memory[0xfb90] = 0x44;
  memory[0xfb91] = 0xc1;
  memory[0xc144] = 0x16;
  memory[0xc145] = 0x82;
  memory[0x8216] = 0x64;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x8216);
  EXPECT_EQ(cpu.get_SP(), 0x7b);
  EXPECT_EQ(cpu.get_A(), 0x19);
  EXPECT_EQ(cpu.get_X(), 0xc2);
  EXPECT_EQ(cpu.get_Y(), 0x03);
  EXPECT_EQ(cpu.get_P(), 0xef);

  EXPECT_EQ(memory[0x8216], 0x64);
  EXPECT_EQ(memory[0xc144], 0x16);
  EXPECT_EQ(memory[0xc145], 0x82);
  EXPECT_EQ(memory[0xfb8f], 0x6c);
  EXPECT_EQ(memory[0xfb90], 0x44);
  EXPECT_EQ(memory[0xfb91], 0xc1);
}
TEST(CPU, instruction_ADC_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x6d";

  constexpr std::uint16_t PC = 0x2ea7;
  constexpr uint8_t SP = 0x67;
  constexpr uint8_t A = 0x43;
  constexpr uint8_t X = 0x27;
  constexpr uint8_t Y = 0x18;
  constexpr uint8_t P = 0xe8;

  memory[0x2ea7] = 0x6d;
  memory[0x2ea8] = 0x9b;
  memory[0x2ea9] = 0x6c;
  memory[0x6c9b] = 0x71;
  memory[0x2eaa] = 0xe6;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x2eaa);
  EXPECT_EQ(cpu.get_SP(), 0x67);
  EXPECT_EQ(cpu.get_A(), 0x14);
  EXPECT_EQ(cpu.get_X(), 0x27);
  EXPECT_EQ(cpu.get_Y(), 0x18);
  EXPECT_EQ(cpu.get_P(), 0xe9);

  EXPECT_EQ(memory[0x2ea7], 0x6d);
  EXPECT_EQ(memory[0x2ea8], 0x9b);
  EXPECT_EQ(memory[0x2ea9], 0x6c);
  EXPECT_EQ(memory[0x2eaa], 0xe6);
  EXPECT_EQ(memory[0x6c9b], 0x71);
}
TEST(CPU, instruction_ROR_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x6e";

  constexpr std::uint16_t PC = 0xb105;
  constexpr uint8_t SP = 0x6d;
  constexpr uint8_t A = 0x4c;
  constexpr uint8_t X = 0x2b;
  constexpr uint8_t Y = 0xab;
  constexpr uint8_t P = 0xaf;

  memory[0xb105] = 0x6e;
  memory[0xb106] = 0x76;
  memory[0xb107] = 0x7c;
  memory[0x7c76] = 0xb9;
  memory[0xb108] = 0x8b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xb108);
  EXPECT_EQ(cpu.get_SP(), 0x6d);
  EXPECT_EQ(cpu.get_A(), 0x4c);
  EXPECT_EQ(cpu.get_X(), 0x2b);
  EXPECT_EQ(cpu.get_Y(), 0xab);
  EXPECT_EQ(cpu.get_P(), 0xad);

  EXPECT_EQ(memory[0x7c76], 0xdc);
  EXPECT_EQ(memory[0xb105], 0x6e);
  EXPECT_EQ(memory[0xb106], 0x76);
  EXPECT_EQ(memory[0xb107], 0x7c);
  EXPECT_EQ(memory[0xb108], 0x8b);
}
TEST(CPU, instruction_BVS_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x70";

  constexpr std::uint16_t PC = 0x13b4;
  constexpr uint8_t SP = 0xad;
  constexpr uint8_t A = 0x55;
  constexpr uint8_t X = 0xf6;
  constexpr uint8_t Y = 0x24;
  constexpr uint8_t P = 0xac;

  memory[0x13b4] = 0x70;
  memory[0x13b5] = 0x5c;
  memory[0x13b6] = 0x05;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x13b6);
  EXPECT_EQ(cpu.get_SP(), 0xad);
  EXPECT_EQ(cpu.get_A(), 0x55);
  EXPECT_EQ(cpu.get_X(), 0xf6);
  EXPECT_EQ(cpu.get_Y(), 0x24);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x13b4], 0x70);
  EXPECT_EQ(memory[0x13b5], 0x5c);
  EXPECT_EQ(memory[0x13b6], 0x05);
}
TEST(CPU, instruction_ADC_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x71";

  constexpr std::uint16_t PC = 0xe089;
  constexpr uint8_t SP = 0x3a;
  constexpr uint8_t A = 0x78;
  constexpr uint8_t X = 0x6b;
  constexpr uint8_t Y = 0xe9;
  constexpr uint8_t P = 0x25;

  memory[0xe089] = 0x71;
  memory[0xe08a] = 0x20;
  memory[0xe08b] = 0x6d;
  memory[0x0020] = 0x90;
  memory[0x0021] = 0x51;
  memory[0x5179] = 0x46;
  memory[0x5279] = 0x67;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xe08b);
  EXPECT_EQ(cpu.get_SP(), 0x3a);
  EXPECT_EQ(cpu.get_A(), 0xe0);
  EXPECT_EQ(cpu.get_X(), 0x6b);
  EXPECT_EQ(cpu.get_Y(), 0xe9);
  EXPECT_EQ(cpu.get_P(), 0xe4);

  EXPECT_EQ(memory[0x0020], 0x90);
  EXPECT_EQ(memory[0x0021], 0x51);
  EXPECT_EQ(memory[0x5179], 0x46);
  EXPECT_EQ(memory[0x5279], 0x67);
  EXPECT_EQ(memory[0xe089], 0x71);
  EXPECT_EQ(memory[0xe08a], 0x20);
  EXPECT_EQ(memory[0xe08b], 0x6d);
}
TEST(CPU, instruction_ADC_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x75";

  constexpr std::uint16_t PC = 0xb26c;
  constexpr uint8_t SP = 0x35;
  constexpr uint8_t A = 0x57;
  constexpr uint8_t X = 0x9c;
  constexpr uint8_t Y = 0x2d;
  constexpr uint8_t P = 0xe2;

  memory[0xb26c] = 0x75;
  memory[0xb26d] = 0x5f;
  memory[0xb26e] = 0x61;
  memory[0x005f] = 0x86;
  memory[0x00fb] = 0xe7;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xb26e);
  EXPECT_EQ(cpu.get_SP(), 0x35);
  EXPECT_EQ(cpu.get_A(), 0x3e);
  EXPECT_EQ(cpu.get_X(), 0x9c);
  EXPECT_EQ(cpu.get_Y(), 0x2d);
  EXPECT_EQ(cpu.get_P(), 0x21);

  EXPECT_EQ(memory[0x005f], 0x86);
  EXPECT_EQ(memory[0x00fb], 0xe7);
  EXPECT_EQ(memory[0xb26c], 0x75);
  EXPECT_EQ(memory[0xb26d], 0x5f);
  EXPECT_EQ(memory[0xb26e], 0x61);
}
TEST(CPU, instruction_ROR_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x76";

  constexpr std::uint16_t PC = 0x0f7b;
  constexpr uint8_t SP = 0x0a;
  constexpr uint8_t A = 0x19;
  constexpr uint8_t X = 0x6b;
  constexpr uint8_t Y = 0xfe;
  constexpr uint8_t P = 0x61;

  memory[0x0f7b] = 0x76;
  memory[0x0f7c] = 0x67;
  memory[0x0f7d] = 0x88;
  memory[0x0067] = 0x44;
  memory[0x00d2] = 0x79;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0f7d);
  EXPECT_EQ(cpu.get_SP(), 0x0a);
  EXPECT_EQ(cpu.get_A(), 0x19);
  EXPECT_EQ(cpu.get_X(), 0x6b);
  EXPECT_EQ(cpu.get_Y(), 0xfe);
  EXPECT_EQ(cpu.get_P(), 0xe1);

  EXPECT_EQ(memory[0x0067], 0x44);
  EXPECT_EQ(memory[0x00d2], 0xbc);
  EXPECT_EQ(memory[0x0f7b], 0x76);
  EXPECT_EQ(memory[0x0f7c], 0x67);
  EXPECT_EQ(memory[0x0f7d], 0x88);
}
TEST(CPU, instruction_SEI_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x78";

  constexpr std::uint16_t PC = 0x3eb3;
  constexpr uint8_t SP = 0xa0;
  constexpr uint8_t A = 0xa2;
  constexpr uint8_t X = 0x8c;
  constexpr uint8_t Y = 0x01;
  constexpr uint8_t P = 0xa4;

  memory[0x3eb3] = 0x78;
  memory[0x3eb4] = 0xac;
  memory[0x3eb5] = 0x45;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x3eb4);
  EXPECT_EQ(cpu.get_SP(), 0xa0);
  EXPECT_EQ(cpu.get_A(), 0xa2);
  EXPECT_EQ(cpu.get_X(), 0x8c);
  EXPECT_EQ(cpu.get_Y(), 0x01);
  EXPECT_EQ(cpu.get_P(), 0xa4);

  EXPECT_EQ(memory[0x3eb3], 0x78);
  EXPECT_EQ(memory[0x3eb4], 0xac);
  EXPECT_EQ(memory[0x3eb5], 0x45);
}
TEST(CPU, instruction_ADC_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x79";

  constexpr std::uint16_t PC = 0x34cb;
  constexpr uint8_t SP = 0x70;
  constexpr uint8_t A = 0xf1;
  constexpr uint8_t X = 0x14;
  constexpr uint8_t Y = 0x23;
  constexpr uint8_t P = 0xe1;

  memory[0x34cb] = 0x79;
  memory[0x34cc] = 0xad;
  memory[0x34cd] = 0x73;
  memory[0x73d0] = 0x4a;
  memory[0x34ce] = 0x77;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x34ce);
  EXPECT_EQ(cpu.get_SP(), 0x70);
  EXPECT_EQ(cpu.get_A(), 0x3c);
  EXPECT_EQ(cpu.get_X(), 0x14);
  EXPECT_EQ(cpu.get_Y(), 0x23);
  EXPECT_EQ(cpu.get_P(), 0x21);

  EXPECT_EQ(memory[0x34cb], 0x79);
  EXPECT_EQ(memory[0x34cc], 0xad);
  EXPECT_EQ(memory[0x34cd], 0x73);
  EXPECT_EQ(memory[0x34ce], 0x77);
  EXPECT_EQ(memory[0x73d0], 0x4a);
}
TEST(CPU, instruction_ADC_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x7d";

  constexpr std::uint16_t PC = 0x2fb4;
  constexpr uint8_t SP = 0x35;
  constexpr uint8_t A = 0x9b;
  constexpr uint8_t X = 0x09;
  constexpr uint8_t Y = 0x76;
  constexpr uint8_t P = 0xa6;

  memory[0x2fb4] = 0x7d;
  memory[0x2fb5] = 0x4d;
  memory[0x2fb6] = 0x93;
  memory[0x9356] = 0x03;
  memory[0x2fb7] = 0x48;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x2fb7);
  EXPECT_EQ(cpu.get_SP(), 0x35);
  EXPECT_EQ(cpu.get_A(), 0x9e);
  EXPECT_EQ(cpu.get_X(), 0x09);
  EXPECT_EQ(cpu.get_Y(), 0x76);
  EXPECT_EQ(cpu.get_P(), 0xa4);

  EXPECT_EQ(memory[0x2fb4], 0x7d);
  EXPECT_EQ(memory[0x2fb5], 0x4d);
  EXPECT_EQ(memory[0x2fb6], 0x93);
  EXPECT_EQ(memory[0x2fb7], 0x48);
  EXPECT_EQ(memory[0x9356], 0x03);
}
TEST(CPU, instruction_ROR_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x7e";

  constexpr std::uint16_t PC = 0xa299;
  constexpr uint8_t SP = 0x36;
  constexpr uint8_t A = 0x89;
  constexpr uint8_t X = 0x32;
  constexpr uint8_t Y = 0x8a;
  constexpr uint8_t P = 0x2d;

  memory[0xa299] = 0x7e;
  memory[0xa29a] = 0x80;
  memory[0xa29b] = 0x8a;
  memory[0x8ab2] = 0x53;
  memory[0xa29c] = 0x7f;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa29c);
  EXPECT_EQ(cpu.get_SP(), 0x36);
  EXPECT_EQ(cpu.get_A(), 0x89);
  EXPECT_EQ(cpu.get_X(), 0x32);
  EXPECT_EQ(cpu.get_Y(), 0x8a);
  EXPECT_EQ(cpu.get_P(), 0xad);

  EXPECT_EQ(memory[0x8ab2], 0xa9);
  EXPECT_EQ(memory[0xa299], 0x7e);
  EXPECT_EQ(memory[0xa29a], 0x80);
  EXPECT_EQ(memory[0xa29b], 0x8a);
  EXPECT_EQ(memory[0xa29c], 0x7f);
}
TEST(CPU, instruction_STA_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x81";

  constexpr std::uint16_t PC = 0x276d;
  constexpr uint8_t SP = 0xec;
  constexpr uint8_t A = 0x16;
  constexpr uint8_t X = 0x35;
  constexpr uint8_t Y = 0x62;
  constexpr uint8_t P = 0x2b;

  memory[0x276d] = 0x81;
  memory[0x276e] = 0xd9;
  memory[0x276f] = 0x28;
  memory[0x00d9] = 0xdd;
  memory[0x000e] = 0x64;
  memory[0x000f] = 0x4c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x276f);
  EXPECT_EQ(cpu.get_SP(), 0xec);
  EXPECT_EQ(cpu.get_A(), 0x16);
  EXPECT_EQ(cpu.get_X(), 0x35);
  EXPECT_EQ(cpu.get_Y(), 0x62);
  EXPECT_EQ(cpu.get_P(), 0x2b);

  EXPECT_EQ(memory[0x000e], 0x64);
  EXPECT_EQ(memory[0x000f], 0x4c);
  EXPECT_EQ(memory[0x00d9], 0xdd);
  EXPECT_EQ(memory[0x276d], 0x81);
  EXPECT_EQ(memory[0x276e], 0xd9);
  EXPECT_EQ(memory[0x276f], 0x28);
  EXPECT_EQ(memory[0x4c64], 0x16);
}
TEST(CPU, instruction_STY_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x84";

  constexpr std::uint16_t PC = 0xa08c;
  constexpr uint8_t SP = 0x42;
  constexpr uint8_t A = 0x60;
  constexpr uint8_t X = 0x1c;
  constexpr uint8_t Y = 0x12;
  constexpr uint8_t P = 0x22;

  memory[0xa08c] = 0x84;
  memory[0xa08d] = 0x8f;
  memory[0xa08e] = 0xad;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa08e);
  EXPECT_EQ(cpu.get_SP(), 0x42);
  EXPECT_EQ(cpu.get_A(), 0x60);
  EXPECT_EQ(cpu.get_X(), 0x1c);
  EXPECT_EQ(cpu.get_Y(), 0x12);
  EXPECT_EQ(cpu.get_P(), 0x22);

  EXPECT_EQ(memory[0x008f], 0x12);
  EXPECT_EQ(memory[0xa08c], 0x84);
  EXPECT_EQ(memory[0xa08d], 0x8f);
  EXPECT_EQ(memory[0xa08e], 0xad);
}
TEST(CPU, instruction_STA_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x85";

  constexpr std::uint16_t PC = 0x7f80;
  constexpr uint8_t SP = 0x89;
  constexpr uint8_t A = 0x27;
  constexpr uint8_t X = 0xd4;
  constexpr uint8_t Y = 0x36;
  constexpr uint8_t P = 0xe7;

  memory[0x7f80] = 0x85;
  memory[0x7f81] = 0x64;
  memory[0x7f82] = 0x87;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x7f82);
  EXPECT_EQ(cpu.get_SP(), 0x89);
  EXPECT_EQ(cpu.get_A(), 0x27);
  EXPECT_EQ(cpu.get_X(), 0xd4);
  EXPECT_EQ(cpu.get_Y(), 0x36);
  EXPECT_EQ(cpu.get_P(), 0xe7);

  EXPECT_EQ(memory[0x0064], 0x27);
  EXPECT_EQ(memory[0x7f80], 0x85);
  EXPECT_EQ(memory[0x7f81], 0x64);
  EXPECT_EQ(memory[0x7f82], 0x87);
}
TEST(CPU, instruction_STX_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x86";

  constexpr std::uint16_t PC = 0x4879;
  constexpr uint8_t SP = 0x68;
  constexpr uint8_t A = 0xcf;
  constexpr uint8_t X = 0xd2;
  constexpr uint8_t Y = 0x78;
  constexpr uint8_t P = 0x67;

  memory[0x4879] = 0x86;
  memory[0x487a] = 0x93;
  memory[0x487b] = 0x8d;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x487b);
  EXPECT_EQ(cpu.get_SP(), 0x68);
  EXPECT_EQ(cpu.get_A(), 0xcf);
  EXPECT_EQ(cpu.get_X(), 0xd2);
  EXPECT_EQ(cpu.get_Y(), 0x78);
  EXPECT_EQ(cpu.get_P(), 0x67);

  EXPECT_EQ(memory[0x0093], 0xd2);
  EXPECT_EQ(memory[0x4879], 0x86);
  EXPECT_EQ(memory[0x487a], 0x93);
  EXPECT_EQ(memory[0x487b], 0x8d);
}
TEST(CPU, instruction_DEY_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x88";

  constexpr std::uint16_t PC = 0x287c;
  constexpr uint8_t SP = 0xd7;
  constexpr uint8_t A = 0xa4;
  constexpr uint8_t X = 0x78;
  constexpr uint8_t Y = 0x5b;
  constexpr uint8_t P = 0x6e;

  memory[0x287c] = 0x88;
  memory[0x287d] = 0x1b;
  memory[0x287e] = 0x40;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x287d);
  EXPECT_EQ(cpu.get_SP(), 0xd7);
  EXPECT_EQ(cpu.get_A(), 0xa4);
  EXPECT_EQ(cpu.get_X(), 0x78);
  EXPECT_EQ(cpu.get_Y(), 0x5a);
  EXPECT_EQ(cpu.get_P(), 0x6c);

  EXPECT_EQ(memory[0x287c], 0x88);
  EXPECT_EQ(memory[0x287d], 0x1b);
  EXPECT_EQ(memory[0x287e], 0x40);
}
TEST(CPU, instruction_TXA_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x8a";

  constexpr std::uint16_t PC = 0x34e9;
  constexpr uint8_t SP = 0xde;
  constexpr uint8_t A = 0x96;
  constexpr uint8_t X = 0x29;
  constexpr uint8_t Y = 0x32;
  constexpr uint8_t P = 0xa1;

  memory[0x34e9] = 0x8a;
  memory[0x34ea] = 0xfb;
  memory[0x34eb] = 0x59;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x34ea);
  EXPECT_EQ(cpu.get_SP(), 0xde);
  EXPECT_EQ(cpu.get_A(), 0x29);
  EXPECT_EQ(cpu.get_X(), 0x29);
  EXPECT_EQ(cpu.get_Y(), 0x32);
  EXPECT_EQ(cpu.get_P(), 0x21);

  EXPECT_EQ(memory[0x34e9], 0x8a);
  EXPECT_EQ(memory[0x34ea], 0xfb);
  EXPECT_EQ(memory[0x34eb], 0x59);
}
TEST(CPU, instruction_STY_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x8c";

  constexpr std::uint16_t PC = 0x84aa;
  constexpr uint8_t SP = 0x58;
  constexpr uint8_t A = 0x85;
  constexpr uint8_t X = 0xe6;
  constexpr uint8_t Y = 0x7e;
  constexpr uint8_t P = 0x67;

  memory[0x84aa] = 0x8c;
  memory[0x84ab] = 0xc0;
  memory[0x84ac] = 0x13;
  memory[0x84ad] = 0x0a;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x84ad);
  EXPECT_EQ(cpu.get_SP(), 0x58);
  EXPECT_EQ(cpu.get_A(), 0x85);
  EXPECT_EQ(cpu.get_X(), 0xe6);
  EXPECT_EQ(cpu.get_Y(), 0x7e);
  EXPECT_EQ(cpu.get_P(), 0x67);

  EXPECT_EQ(memory[0x13c0], 0x7e);
  EXPECT_EQ(memory[0x84aa], 0x8c);
  EXPECT_EQ(memory[0x84ab], 0xc0);
  EXPECT_EQ(memory[0x84ac], 0x13);
  EXPECT_EQ(memory[0x84ad], 0x0a);
}
TEST(CPU, instruction_STA_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x8d";

  constexpr std::uint16_t PC = 0x376c;
  constexpr uint8_t SP = 0x73;
  constexpr uint8_t A = 0xfd;
  constexpr uint8_t X = 0xe5;
  constexpr uint8_t Y = 0xc4;
  constexpr uint8_t P = 0x65;

  memory[0x376c] = 0x8d;
  memory[0x376d] = 0x0d;
  memory[0x376e] = 0x22;
  memory[0x376f] = 0xe6;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x376f);
  EXPECT_EQ(cpu.get_SP(), 0x73);
  EXPECT_EQ(cpu.get_A(), 0xfd);
  EXPECT_EQ(cpu.get_X(), 0xe5);
  EXPECT_EQ(cpu.get_Y(), 0xc4);
  EXPECT_EQ(cpu.get_P(), 0x65);

  EXPECT_EQ(memory[0x220d], 0xfd);
  EXPECT_EQ(memory[0x376c], 0x8d);
  EXPECT_EQ(memory[0x376d], 0x0d);
  EXPECT_EQ(memory[0x376e], 0x22);
  EXPECT_EQ(memory[0x376f], 0xe6);
}
TEST(CPU, instruction_STX_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x8e";

  constexpr std::uint16_t PC = 0x1009;
  constexpr uint8_t SP = 0x8b;
  constexpr uint8_t A = 0x89;
  constexpr uint8_t X = 0x64;
  constexpr uint8_t Y = 0xa3;
  constexpr uint8_t P = 0xa9;

  memory[0x1009] = 0x8e;
  memory[0x100a] = 0x22;
  memory[0x100b] = 0xc0;
  memory[0x100c] = 0x5c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x100c);
  EXPECT_EQ(cpu.get_SP(), 0x8b);
  EXPECT_EQ(cpu.get_A(), 0x89);
  EXPECT_EQ(cpu.get_X(), 0x64);
  EXPECT_EQ(cpu.get_Y(), 0xa3);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x1009], 0x8e);
  EXPECT_EQ(memory[0x100a], 0x22);
  EXPECT_EQ(memory[0x100b], 0xc0);
  EXPECT_EQ(memory[0x100c], 0x5c);
  EXPECT_EQ(memory[0xc022], 0x64);
}
TEST(CPU, instruction_BCC_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x90";

  constexpr std::uint16_t PC = 0xec80;
  constexpr uint8_t SP = 0xcd;
  constexpr uint8_t A = 0x24;
  constexpr uint8_t X = 0xcf;
  constexpr uint8_t Y = 0xb3;
  constexpr uint8_t P = 0x20;

  memory[0xec80] = 0x90;
  memory[0xec81] = 0xc6;
  memory[0xec82] = 0x7a;
  memory[0xec48] = 0xd6;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xec48);
  EXPECT_EQ(cpu.get_SP(), 0xcd);
  EXPECT_EQ(cpu.get_A(), 0x24);
  EXPECT_EQ(cpu.get_X(), 0xcf);
  EXPECT_EQ(cpu.get_Y(), 0xb3);
  EXPECT_EQ(cpu.get_P(), 0x20);

  EXPECT_EQ(memory[0xec48], 0xd6);
  EXPECT_EQ(memory[0xec80], 0x90);
  EXPECT_EQ(memory[0xec81], 0xc6);
  EXPECT_EQ(memory[0xec82], 0x7a);
}
TEST(CPU, instruction_STA_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x91";

  constexpr std::uint16_t PC = 0x1c86;
  constexpr uint8_t SP = 0x95;
  constexpr uint8_t A = 0x3f;
  constexpr uint8_t X = 0x11;
  constexpr uint8_t Y = 0x1c;
  constexpr uint8_t P = 0x2b;

  memory[0x1c86] = 0x91;
  memory[0x1c87] = 0xbb;
  memory[0x1c88] = 0x6e;
  memory[0x00bb] = 0x8d;
  memory[0x00bc] = 0x59;
  memory[0x59a9] = 0xd5;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x1c88);
  EXPECT_EQ(cpu.get_SP(), 0x95);
  EXPECT_EQ(cpu.get_A(), 0x3f);
  EXPECT_EQ(cpu.get_X(), 0x11);
  EXPECT_EQ(cpu.get_Y(), 0x1c);
  EXPECT_EQ(cpu.get_P(), 0x2b);

  EXPECT_EQ(memory[0x00bb], 0x8d);
  EXPECT_EQ(memory[0x00bc], 0x59);
  EXPECT_EQ(memory[0x1c86], 0x91);
  EXPECT_EQ(memory[0x1c87], 0xbb);
  EXPECT_EQ(memory[0x1c88], 0x6e);
  EXPECT_EQ(memory[0x59a9], 0x3f);
}
TEST(CPU, instruction_STY_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x94";

  constexpr std::uint16_t PC = 0xaed9;
  constexpr uint8_t SP = 0xbf;
  constexpr uint8_t A = 0x0c;
  constexpr uint8_t X = 0xc9;
  constexpr uint8_t Y = 0x83;
  constexpr uint8_t P = 0xab;

  memory[0xaed9] = 0x94;
  memory[0xaeda] = 0x8e;
  memory[0xaedb] = 0x63;
  memory[0x008e] = 0x82;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xaedb);
  EXPECT_EQ(cpu.get_SP(), 0xbf);
  EXPECT_EQ(cpu.get_A(), 0x0c);
  EXPECT_EQ(cpu.get_X(), 0xc9);
  EXPECT_EQ(cpu.get_Y(), 0x83);
  EXPECT_EQ(cpu.get_P(), 0xab);

  EXPECT_EQ(memory[0x0057], 0x83);
  EXPECT_EQ(memory[0x008e], 0x82);
  EXPECT_EQ(memory[0xaed9], 0x94);
  EXPECT_EQ(memory[0xaeda], 0x8e);
  EXPECT_EQ(memory[0xaedb], 0x63);
}
TEST(CPU, instruction_STA_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x95";

  constexpr std::uint16_t PC = 0x0bf2;
  constexpr uint8_t SP = 0x7f;
  constexpr uint8_t A = 0x62;
  constexpr uint8_t X = 0x95;
  constexpr uint8_t Y = 0x9e;
  constexpr uint8_t P = 0x6c;

  memory[0x0bf2] = 0x95;
  memory[0x0bf3] = 0xac;
  memory[0x0bf4] = 0x90;
  memory[0x00ac] = 0x3c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0bf4);
  EXPECT_EQ(cpu.get_SP(), 0x7f);
  EXPECT_EQ(cpu.get_A(), 0x62);
  EXPECT_EQ(cpu.get_X(), 0x95);
  EXPECT_EQ(cpu.get_Y(), 0x9e);
  EXPECT_EQ(cpu.get_P(), 0x6c);

  EXPECT_EQ(memory[0x0041], 0x62);
  EXPECT_EQ(memory[0x00ac], 0x3c);
  EXPECT_EQ(memory[0x0bf2], 0x95);
  EXPECT_EQ(memory[0x0bf3], 0xac);
  EXPECT_EQ(memory[0x0bf4], 0x90);
}
TEST(CPU, instruction_STX_zero_page_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x96";

  constexpr std::uint16_t PC = 0xfb9c;
  constexpr uint8_t SP = 0xf7;
  constexpr uint8_t A = 0x21;
  constexpr uint8_t X = 0xae;
  constexpr uint8_t Y = 0x09;
  constexpr uint8_t P = 0x65;

  memory[0xfb9c] = 0x96;
  memory[0xfb9d] = 0xd2;
  memory[0xfb9e] = 0xd3;
  memory[0x00d2] = 0xe7;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xfb9e);
  EXPECT_EQ(cpu.get_SP(), 0xf7);
  EXPECT_EQ(cpu.get_A(), 0x21);
  EXPECT_EQ(cpu.get_X(), 0xae);
  EXPECT_EQ(cpu.get_Y(), 0x09);
  EXPECT_EQ(cpu.get_P(), 0x65);

  EXPECT_EQ(memory[0x00d2], 0xe7);
  EXPECT_EQ(memory[0x00db], 0xae);
  EXPECT_EQ(memory[0xfb9c], 0x96);
  EXPECT_EQ(memory[0xfb9d], 0xd2);
  EXPECT_EQ(memory[0xfb9e], 0xd3);
}
TEST(CPU, instruction_TYA_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x98";

  constexpr std::uint16_t PC = 0xaefb;
  constexpr uint8_t SP = 0x23;
  constexpr uint8_t A = 0x78;
  constexpr uint8_t X = 0x39;
  constexpr uint8_t Y = 0x03;
  constexpr uint8_t P = 0xea;

  memory[0xaefb] = 0x98;
  memory[0xaefc] = 0xdd;
  memory[0xaefd] = 0x23;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xaefc);
  EXPECT_EQ(cpu.get_SP(), 0x23);
  EXPECT_EQ(cpu.get_A(), 0x03);
  EXPECT_EQ(cpu.get_X(), 0x39);
  EXPECT_EQ(cpu.get_Y(), 0x03);
  EXPECT_EQ(cpu.get_P(), 0x68);

  EXPECT_EQ(memory[0xaefb], 0x98);
  EXPECT_EQ(memory[0xaefc], 0xdd);
  EXPECT_EQ(memory[0xaefd], 0x23);
}
TEST(CPU, instruction_STA_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x99";

  constexpr std::uint16_t PC = 0x7b81;
  constexpr uint8_t SP = 0x1a;
  constexpr uint8_t A = 0x0e;
  constexpr uint8_t X = 0xf4;
  constexpr uint8_t Y = 0x03;
  constexpr uint8_t P = 0x6f;

  memory[0x7b81] = 0x99;
  memory[0x7b82] = 0xaf;
  memory[0x7b83] = 0x0f;
  memory[0x0fb2] = 0xf6;
  memory[0x7b84] = 0x1f;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x7b84);
  EXPECT_EQ(cpu.get_SP(), 0x1a);
  EXPECT_EQ(cpu.get_A(), 0x0e);
  EXPECT_EQ(cpu.get_X(), 0xf4);
  EXPECT_EQ(cpu.get_Y(), 0x03);
  EXPECT_EQ(cpu.get_P(), 0x6f);

  EXPECT_EQ(memory[0x0fb2], 0x0e);
  EXPECT_EQ(memory[0x7b81], 0x99);
  EXPECT_EQ(memory[0x7b82], 0xaf);
  EXPECT_EQ(memory[0x7b83], 0x0f);
  EXPECT_EQ(memory[0x7b84], 0x1f);
}
TEST(CPU, instruction_TXS_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x9a";

  constexpr std::uint16_t PC = 0x18d5;
  constexpr uint8_t SP = 0xe1;
  constexpr uint8_t A = 0xf4;
  constexpr uint8_t X = 0x29;
  constexpr uint8_t Y = 0xe7;
  constexpr uint8_t P = 0x22;

  memory[0x18d5] = 0x9a;
  memory[0x18d6] = 0x0b;
  memory[0x18d7] = 0xd0;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x18d6);
  EXPECT_EQ(cpu.get_SP(), 0x29);
  EXPECT_EQ(cpu.get_A(), 0xf4);
  EXPECT_EQ(cpu.get_X(), 0x29);
  EXPECT_EQ(cpu.get_Y(), 0xe7);
  EXPECT_EQ(cpu.get_P(), 0x22);

  EXPECT_EQ(memory[0x18d5], 0x9a);
  EXPECT_EQ(memory[0x18d6], 0x0b);
  EXPECT_EQ(memory[0x18d7], 0xd0);
}
TEST(CPU, instruction_STA_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0x9d";

  constexpr std::uint16_t PC = 0x7878;
  constexpr uint8_t SP = 0x74;
  constexpr uint8_t A = 0x33;
  constexpr uint8_t X = 0xe2;
  constexpr uint8_t Y = 0xe2;
  constexpr uint8_t P = 0x63;

  memory[0x7878] = 0x9d;
  memory[0x7879] = 0xb8;
  memory[0x787a] = 0xad;
  memory[0xad9a] = 0x77;
  memory[0x787b] = 0x87;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x787b);
  EXPECT_EQ(cpu.get_SP(), 0x74);
  EXPECT_EQ(cpu.get_A(), 0x33);
  EXPECT_EQ(cpu.get_X(), 0xe2);
  EXPECT_EQ(cpu.get_Y(), 0xe2);
  EXPECT_EQ(cpu.get_P(), 0x63);

  EXPECT_EQ(memory[0x7878], 0x9d);
  EXPECT_EQ(memory[0x7879], 0xb8);
  EXPECT_EQ(memory[0x787a], 0xad);
  EXPECT_EQ(memory[0x787b], 0x87);
  EXPECT_EQ(memory[0xad9a], 0x77);
  EXPECT_EQ(memory[0xae9a], 0x33);
}
TEST(CPU, instruction_LDY_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa0";

  constexpr std::uint16_t PC = 0x70bd;
  constexpr uint8_t SP = 0xc4;
  constexpr uint8_t A = 0x9a;
  constexpr uint8_t X = 0xe0;
  constexpr uint8_t Y = 0x6b;
  constexpr uint8_t P = 0x28;

  memory[0x70bd] = 0xa0;
  memory[0x70be] = 0xc9;
  memory[0x70bf] = 0xc1;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x70bf);
  EXPECT_EQ(cpu.get_SP(), 0xc4);
  EXPECT_EQ(cpu.get_A(), 0x9a);
  EXPECT_EQ(cpu.get_X(), 0xe0);
  EXPECT_EQ(cpu.get_Y(), 0xc9);
  EXPECT_EQ(cpu.get_P(), 0xa8);

  EXPECT_EQ(memory[0x70bd], 0xa0);
  EXPECT_EQ(memory[0x70be], 0xc9);
  EXPECT_EQ(memory[0x70bf], 0xc1);
}
TEST(CPU, instruction_LDA_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa1";

  constexpr std::uint16_t PC = 0xa6b5;
  constexpr uint8_t SP = 0xb2;
  constexpr uint8_t A = 0x04;
  constexpr uint8_t X = 0x8e;
  constexpr uint8_t Y = 0x01;
  constexpr uint8_t P = 0x26;

  memory[0xa6b5] = 0xa1;
  memory[0xa6b6] = 0xb0;
  memory[0xa6b7] = 0xa1;
  memory[0x00b0] = 0x8a;
  memory[0x003e] = 0x18;
  memory[0x003f] = 0x5b;
  memory[0x5b18] = 0x45;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa6b7);
  EXPECT_EQ(cpu.get_SP(), 0xb2);
  EXPECT_EQ(cpu.get_A(), 0x45);
  EXPECT_EQ(cpu.get_X(), 0x8e);
  EXPECT_EQ(cpu.get_Y(), 0x01);
  EXPECT_EQ(cpu.get_P(), 0x24);

  EXPECT_EQ(memory[0x003e], 0x18);
  EXPECT_EQ(memory[0x003f], 0x5b);
  EXPECT_EQ(memory[0x00b0], 0x8a);
  EXPECT_EQ(memory[0x5b18], 0x45);
  EXPECT_EQ(memory[0xa6b5], 0xa1);
  EXPECT_EQ(memory[0xa6b6], 0xb0);
  EXPECT_EQ(memory[0xa6b7], 0xa1);
}
TEST(CPU, instruction_LDX_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa2";

  constexpr std::uint16_t PC = 0xb02b;
  constexpr uint8_t SP = 0x26;
  constexpr uint8_t A = 0x2b;
  constexpr uint8_t X = 0x6e;
  constexpr uint8_t Y = 0x51;
  constexpr uint8_t P = 0x27;

  memory[0xb02b] = 0xa2;
  memory[0xb02c] = 0x72;
  memory[0xb02d] = 0x42;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xb02d);
  EXPECT_EQ(cpu.get_SP(), 0x26);
  EXPECT_EQ(cpu.get_A(), 0x2b);
  EXPECT_EQ(cpu.get_X(), 0x72);
  EXPECT_EQ(cpu.get_Y(), 0x51);
  EXPECT_EQ(cpu.get_P(), 0x25);

  EXPECT_EQ(memory[0xb02b], 0xa2);
  EXPECT_EQ(memory[0xb02c], 0x72);
  EXPECT_EQ(memory[0xb02d], 0x42);
}
TEST(CPU, instruction_LDY_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa4";

  constexpr std::uint16_t PC = 0xfeac;
  constexpr uint8_t SP = 0x21;
  constexpr uint8_t A = 0x52;
  constexpr uint8_t X = 0xce;
  constexpr uint8_t Y = 0xbe;
  constexpr uint8_t P = 0x22;

  memory[0xfeac] = 0xa4;
  memory[0xfead] = 0x8a;
  memory[0xfeae] = 0x1c;
  memory[0x008a] = 0x5a;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xfeae);
  EXPECT_EQ(cpu.get_SP(), 0x21);
  EXPECT_EQ(cpu.get_A(), 0x52);
  EXPECT_EQ(cpu.get_X(), 0xce);
  EXPECT_EQ(cpu.get_Y(), 0x5a);
  EXPECT_EQ(cpu.get_P(), 0x20);

  EXPECT_EQ(memory[0x008a], 0x5a);
  EXPECT_EQ(memory[0xfeac], 0xa4);
  EXPECT_EQ(memory[0xfead], 0x8a);
  EXPECT_EQ(memory[0xfeae], 0x1c);
}
TEST(CPU, instruction_LDA_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa5";

  constexpr std::uint16_t PC = 0x8b9e;
  constexpr uint8_t SP = 0x9b;
  constexpr uint8_t A = 0xed;
  constexpr uint8_t X = 0x68;
  constexpr uint8_t Y = 0x94;
  constexpr uint8_t P = 0xe3;

  memory[0x8b9e] = 0xa5;
  memory[0x8b9f] = 0x35;
  memory[0x8ba0] = 0x39;
  memory[0x0035] = 0x7e;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x8ba0);
  EXPECT_EQ(cpu.get_SP(), 0x9b);
  EXPECT_EQ(cpu.get_A(), 0x7e);
  EXPECT_EQ(cpu.get_X(), 0x68);
  EXPECT_EQ(cpu.get_Y(), 0x94);
  EXPECT_EQ(cpu.get_P(), 0x61);

  EXPECT_EQ(memory[0x0035], 0x7e);
  EXPECT_EQ(memory[0x8b9e], 0xa5);
  EXPECT_EQ(memory[0x8b9f], 0x35);
  EXPECT_EQ(memory[0x8ba0], 0x39);
}
TEST(CPU, instruction_LDX_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa6";

  constexpr std::uint16_t PC = 0xca1a;
  constexpr uint8_t SP = 0x1f;
  constexpr uint8_t A = 0x8d;
  constexpr uint8_t X = 0x5c;
  constexpr uint8_t Y = 0x23;
  constexpr uint8_t P = 0xe2;

  memory[0xca1a] = 0xa6;
  memory[0xca1b] = 0x85;
  memory[0xca1c] = 0xfd;
  memory[0x0085] = 0x52;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xca1c);
  EXPECT_EQ(cpu.get_SP(), 0x1f);
  EXPECT_EQ(cpu.get_A(), 0x8d);
  EXPECT_EQ(cpu.get_X(), 0x52);
  EXPECT_EQ(cpu.get_Y(), 0x23);
  EXPECT_EQ(cpu.get_P(), 0x60);

  EXPECT_EQ(memory[0x0085], 0x52);
  EXPECT_EQ(memory[0xca1a], 0xa6);
  EXPECT_EQ(memory[0xca1b], 0x85);
  EXPECT_EQ(memory[0xca1c], 0xfd);
}
TEST(CPU, instruction_TAY_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa8";

  constexpr std::uint16_t PC = 0x2c9f;
  constexpr uint8_t SP = 0x78;
  constexpr uint8_t A = 0xa8;
  constexpr uint8_t X = 0xa1;
  constexpr uint8_t Y = 0xdb;
  constexpr uint8_t P = 0xe0;

  memory[0x2c9f] = 0xa8;
  memory[0x2ca0] = 0x07;
  memory[0x2ca1] = 0x46;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x2ca0);
  EXPECT_EQ(cpu.get_SP(), 0x78);
  EXPECT_EQ(cpu.get_A(), 0xa8);
  EXPECT_EQ(cpu.get_X(), 0xa1);
  EXPECT_EQ(cpu.get_Y(), 0xa8);
  EXPECT_EQ(cpu.get_P(), 0xe0);

  EXPECT_EQ(memory[0x2c9f], 0xa8);
  EXPECT_EQ(memory[0x2ca0], 0x07);
  EXPECT_EQ(memory[0x2ca1], 0x46);
}
TEST(CPU, instruction_LDA_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xa9";

  constexpr std::uint16_t PC = 0xb36a;
  constexpr uint8_t SP = 0xac;
  constexpr uint8_t A = 0x43;
  constexpr uint8_t X = 0x91;
  constexpr uint8_t Y = 0x96;
  constexpr uint8_t P = 0xed;

  memory[0xb36a] = 0xa9;
  memory[0xb36b] = 0xcc;
  memory[0xb36c] = 0x21;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xb36c);
  EXPECT_EQ(cpu.get_SP(), 0xac);
  EXPECT_EQ(cpu.get_A(), 0xcc);
  EXPECT_EQ(cpu.get_X(), 0x91);
  EXPECT_EQ(cpu.get_Y(), 0x96);
  EXPECT_EQ(cpu.get_P(), 0xed);

  EXPECT_EQ(memory[0xb36a], 0xa9);
  EXPECT_EQ(memory[0xb36b], 0xcc);
  EXPECT_EQ(memory[0xb36c], 0x21);
}
TEST(CPU, instruction_TAX_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xaa";

  constexpr std::uint16_t PC = 0x5aa1;
  constexpr uint8_t SP = 0x9e;
  constexpr uint8_t A = 0x69;
  constexpr uint8_t X = 0xf3;
  constexpr uint8_t Y = 0x6b;
  constexpr uint8_t P = 0xe5;

  memory[0x5aa1] = 0xaa;
  memory[0x5aa2] = 0x4f;
  memory[0x5aa3] = 0xba;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5aa2);
  EXPECT_EQ(cpu.get_SP(), 0x9e);
  EXPECT_EQ(cpu.get_A(), 0x69);
  EXPECT_EQ(cpu.get_X(), 0x69);
  EXPECT_EQ(cpu.get_Y(), 0x6b);
  EXPECT_EQ(cpu.get_P(), 0x65);

  EXPECT_EQ(memory[0x5aa1], 0xaa);
  EXPECT_EQ(memory[0x5aa2], 0x4f);
  EXPECT_EQ(memory[0x5aa3], 0xba);
}
TEST(CPU, instruction_LDY_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xac";

  constexpr std::uint16_t PC = 0x4208;
  constexpr uint8_t SP = 0x46;
  constexpr uint8_t A = 0xd7;
  constexpr uint8_t X = 0xba;
  constexpr uint8_t Y = 0xb4;
  constexpr uint8_t P = 0xa1;

  memory[0x4208] = 0xac;
  memory[0x4209] = 0xfd;
  memory[0x420a] = 0xdd;
  memory[0xddfd] = 0x09;
  memory[0x420b] = 0x0c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x420b);
  EXPECT_EQ(cpu.get_SP(), 0x46);
  EXPECT_EQ(cpu.get_A(), 0xd7);
  EXPECT_EQ(cpu.get_X(), 0xba);
  EXPECT_EQ(cpu.get_Y(), 0x09);
  EXPECT_EQ(cpu.get_P(), 0x21);

  EXPECT_EQ(memory[0x4208], 0xac);
  EXPECT_EQ(memory[0x4209], 0xfd);
  EXPECT_EQ(memory[0x420a], 0xdd);
  EXPECT_EQ(memory[0x420b], 0x0c);
  EXPECT_EQ(memory[0xddfd], 0x09);
}
TEST(CPU, instruction_LDA_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xad";

  constexpr std::uint16_t PC = 0x7a22;
  constexpr uint8_t SP = 0x65;
  constexpr uint8_t A = 0xdf;
  constexpr uint8_t X = 0x05;
  constexpr uint8_t Y = 0xd8;
  constexpr uint8_t P = 0xe7;

  memory[0x7a22] = 0xad;
  memory[0x7a23] = 0x5e;
  memory[0x7a24] = 0xaf;
  memory[0xaf5e] = 0x67;
  memory[0x7a25] = 0x84;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x7a25);
  EXPECT_EQ(cpu.get_SP(), 0x65);
  EXPECT_EQ(cpu.get_A(), 0x67);
  EXPECT_EQ(cpu.get_X(), 0x05);
  EXPECT_EQ(cpu.get_Y(), 0xd8);
  EXPECT_EQ(cpu.get_P(), 0x65);

  EXPECT_EQ(memory[0x7a22], 0xad);
  EXPECT_EQ(memory[0x7a23], 0x5e);
  EXPECT_EQ(memory[0x7a24], 0xaf);
  EXPECT_EQ(memory[0x7a25], 0x84);
  EXPECT_EQ(memory[0xaf5e], 0x67);
}
TEST(CPU, instruction_LDX_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xae";

  constexpr std::uint16_t PC = 0xd811;
  constexpr uint8_t SP = 0xb6;
  constexpr uint8_t A = 0x35;
  constexpr uint8_t X = 0x92;
  constexpr uint8_t Y = 0x78;
  constexpr uint8_t P = 0xe0;

  memory[0xd811] = 0xae;
  memory[0xd812] = 0x64;
  memory[0xd813] = 0x33;
  memory[0x3364] = 0x22;
  memory[0xd814] = 0xdb;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd814);
  EXPECT_EQ(cpu.get_SP(), 0xb6);
  EXPECT_EQ(cpu.get_A(), 0x35);
  EXPECT_EQ(cpu.get_X(), 0x22);
  EXPECT_EQ(cpu.get_Y(), 0x78);
  EXPECT_EQ(cpu.get_P(), 0x60);

  EXPECT_EQ(memory[0x3364], 0x22);
  EXPECT_EQ(memory[0xd811], 0xae);
  EXPECT_EQ(memory[0xd812], 0x64);
  EXPECT_EQ(memory[0xd813], 0x33);
  EXPECT_EQ(memory[0xd814], 0xdb);
}
TEST(CPU, instruction_BCS_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb0";

  constexpr std::uint16_t PC = 0x3a25;
  constexpr uint8_t SP = 0x18;
  constexpr uint8_t A = 0x55;
  constexpr uint8_t X = 0xfe;
  constexpr uint8_t Y = 0x8c;
  constexpr uint8_t P = 0xac;

  memory[0x3a25] = 0xb0;
  memory[0x3a26] = 0x79;
  memory[0x3a27] = 0xe0;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x3a27);
  EXPECT_EQ(cpu.get_SP(), 0x18);
  EXPECT_EQ(cpu.get_A(), 0x55);
  EXPECT_EQ(cpu.get_X(), 0xfe);
  EXPECT_EQ(cpu.get_Y(), 0x8c);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x3a25], 0xb0);
  EXPECT_EQ(memory[0x3a26], 0x79);
  EXPECT_EQ(memory[0x3a27], 0xe0);
}
TEST(CPU, instruction_LDA_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb1";

  constexpr std::uint16_t PC = 0xa084;
  constexpr uint8_t SP = 0x4e;
  constexpr uint8_t A = 0x9f;
  constexpr uint8_t X = 0x3d;
  constexpr uint8_t Y = 0x99;
  constexpr uint8_t P = 0x66;

  memory[0xa084] = 0xb1;
  memory[0xa085] = 0x90;
  memory[0xa086] = 0x2d;
  memory[0x0090] = 0x56;
  memory[0x0091] = 0x06;
  memory[0x06ef] = 0x99;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa086);
  EXPECT_EQ(cpu.get_SP(), 0x4e);
  EXPECT_EQ(cpu.get_A(), 0x99);
  EXPECT_EQ(cpu.get_X(), 0x3d);
  EXPECT_EQ(cpu.get_Y(), 0x99);
  EXPECT_EQ(cpu.get_P(), 0xe4);

  EXPECT_EQ(memory[0x0090], 0x56);
  EXPECT_EQ(memory[0x0091], 0x06);
  EXPECT_EQ(memory[0x06ef], 0x99);
  EXPECT_EQ(memory[0xa084], 0xb1);
  EXPECT_EQ(memory[0xa085], 0x90);
  EXPECT_EQ(memory[0xa086], 0x2d);
}
TEST(CPU, instruction_LDY_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb4";

  constexpr std::uint16_t PC = 0x9baa;
  constexpr uint8_t SP = 0x6b;
  constexpr uint8_t A = 0x0c;
  constexpr uint8_t X = 0x66;
  constexpr uint8_t Y = 0xb4;
  constexpr uint8_t P = 0x6f;

  memory[0x9baa] = 0xb4;
  memory[0x9bab] = 0xe9;
  memory[0x9bac] = 0x4b;
  memory[0x00e9] = 0xf5;
  memory[0x004f] = 0x06;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x9bac);
  EXPECT_EQ(cpu.get_SP(), 0x6b);
  EXPECT_EQ(cpu.get_A(), 0x0c);
  EXPECT_EQ(cpu.get_X(), 0x66);
  EXPECT_EQ(cpu.get_Y(), 0x06);
  EXPECT_EQ(cpu.get_P(), 0x6d);

  EXPECT_EQ(memory[0x004f], 0x06);
  EXPECT_EQ(memory[0x00e9], 0xf5);
  EXPECT_EQ(memory[0x9baa], 0xb4);
  EXPECT_EQ(memory[0x9bab], 0xe9);
  EXPECT_EQ(memory[0x9bac], 0x4b);
}
TEST(CPU, instruction_LDA_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb5";

  constexpr std::uint16_t PC = 0x4945;
  constexpr uint8_t SP = 0x81;
  constexpr uint8_t A = 0xe8;
  constexpr uint8_t X = 0x5c;
  constexpr uint8_t Y = 0x46;
  constexpr uint8_t P = 0x67;

  memory[0x4945] = 0xb5;
  memory[0x4946] = 0x20;
  memory[0x4947] = 0x39;
  memory[0x0020] = 0xd5;
  memory[0x007c] = 0x2a;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4947);
  EXPECT_EQ(cpu.get_SP(), 0x81);
  EXPECT_EQ(cpu.get_A(), 0x2a);
  EXPECT_EQ(cpu.get_X(), 0x5c);
  EXPECT_EQ(cpu.get_Y(), 0x46);
  EXPECT_EQ(cpu.get_P(), 0x65);

  EXPECT_EQ(memory[0x0020], 0xd5);
  EXPECT_EQ(memory[0x007c], 0x2a);
  EXPECT_EQ(memory[0x4945], 0xb5);
  EXPECT_EQ(memory[0x4946], 0x20);
  EXPECT_EQ(memory[0x4947], 0x39);
}
TEST(CPU, instruction_LDX_zero_page_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb6";

  constexpr std::uint16_t PC = 0x0493;
  constexpr uint8_t SP = 0x55;
  constexpr uint8_t A = 0x42;
  constexpr uint8_t X = 0x89;
  constexpr uint8_t Y = 0x7d;
  constexpr uint8_t P = 0xaf;

  memory[0x0493] = 0xb6;
  memory[0x0494] = 0x39;
  memory[0x0495] = 0xcd;
  memory[0x0039] = 0xc2;
  memory[0x00b6] = 0x66;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0495);
  EXPECT_EQ(cpu.get_SP(), 0x55);
  EXPECT_EQ(cpu.get_A(), 0x42);
  EXPECT_EQ(cpu.get_X(), 0x66);
  EXPECT_EQ(cpu.get_Y(), 0x7d);
  EXPECT_EQ(cpu.get_P(), 0x2d);

  EXPECT_EQ(memory[0x0039], 0xc2);
  EXPECT_EQ(memory[0x00b6], 0x66);
  EXPECT_EQ(memory[0x0493], 0xb6);
  EXPECT_EQ(memory[0x0494], 0x39);
  EXPECT_EQ(memory[0x0495], 0xcd);
}
TEST(CPU, instruction_CLV_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb8";

  constexpr std::uint16_t PC = 0xdfde;
  constexpr uint8_t SP = 0x95;
  constexpr uint8_t A = 0x29;
  constexpr uint8_t X = 0xc9;
  constexpr uint8_t Y = 0x2f;
  constexpr uint8_t P = 0x68;

  memory[0xdfde] = 0xb8;
  memory[0xdfdf] = 0x87;
  memory[0xdfe0] = 0x22;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xdfdf);
  EXPECT_EQ(cpu.get_SP(), 0x95);
  EXPECT_EQ(cpu.get_A(), 0x29);
  EXPECT_EQ(cpu.get_X(), 0xc9);
  EXPECT_EQ(cpu.get_Y(), 0x2f);
  EXPECT_EQ(cpu.get_P(), 0x28);

  EXPECT_EQ(memory[0xdfde], 0xb8);
  EXPECT_EQ(memory[0xdfdf], 0x87);
  EXPECT_EQ(memory[0xdfe0], 0x22);
}
TEST(CPU, instruction_LDA_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xb9";

  constexpr std::uint16_t PC = 0xaaab;
  constexpr uint8_t SP = 0x76;
  constexpr uint8_t A = 0xbe;
  constexpr uint8_t X = 0x08;
  constexpr uint8_t Y = 0xde;
  constexpr uint8_t P = 0xe0;

  memory[0xaaab] = 0xb9;
  memory[0xaaac] = 0x1e;
  memory[0xaaad] = 0xad;
  memory[0xadfc] = 0xb8;
  memory[0xaaae] = 0x7b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xaaae);
  EXPECT_EQ(cpu.get_SP(), 0x76);
  EXPECT_EQ(cpu.get_A(), 0xb8);
  EXPECT_EQ(cpu.get_X(), 0x08);
  EXPECT_EQ(cpu.get_Y(), 0xde);
  EXPECT_EQ(cpu.get_P(), 0xe0);

  EXPECT_EQ(memory[0xaaab], 0xb9);
  EXPECT_EQ(memory[0xaaac], 0x1e);
  EXPECT_EQ(memory[0xaaad], 0xad);
  EXPECT_EQ(memory[0xaaae], 0x7b);
  EXPECT_EQ(memory[0xadfc], 0xb8);
}
TEST(CPU, instruction_TSX_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xba";

  constexpr std::uint16_t PC = 0xe05f;
  constexpr uint8_t SP = 0x10;
  constexpr uint8_t A = 0x6b;
  constexpr uint8_t X = 0x1e;
  constexpr uint8_t Y = 0x4c;
  constexpr uint8_t P = 0xaf;

  memory[0xe05f] = 0xba;
  memory[0xe060] = 0xd6;
  memory[0xe061] = 0x5b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xe060);
  EXPECT_EQ(cpu.get_SP(), 0x10);
  EXPECT_EQ(cpu.get_A(), 0x6b);
  EXPECT_EQ(cpu.get_X(), 0x10);
  EXPECT_EQ(cpu.get_Y(), 0x4c);
  EXPECT_EQ(cpu.get_P(), 0x2d);

  EXPECT_EQ(memory[0xe05f], 0xba);
  EXPECT_EQ(memory[0xe060], 0xd6);
  EXPECT_EQ(memory[0xe061], 0x5b);
}
TEST(CPU, instruction_LDY_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xbc";

  constexpr std::uint16_t PC = 0x85b7;
  constexpr uint8_t SP = 0xa8;
  constexpr uint8_t A = 0x41;
  constexpr uint8_t X = 0xe3;
  constexpr uint8_t Y = 0x07;
  constexpr uint8_t P = 0xa9;

  memory[0x85b7] = 0xbc;
  memory[0x85b8] = 0xe4;
  memory[0x85b9] = 0xdd;
  memory[0xddc7] = 0x04;
  memory[0xdec7] = 0xd5;
  memory[0x85ba] = 0x05;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x85ba);
  EXPECT_EQ(cpu.get_SP(), 0xa8);
  EXPECT_EQ(cpu.get_A(), 0x41);
  EXPECT_EQ(cpu.get_X(), 0xe3);
  EXPECT_EQ(cpu.get_Y(), 0xd5);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x85b7], 0xbc);
  EXPECT_EQ(memory[0x85b8], 0xe4);
  EXPECT_EQ(memory[0x85b9], 0xdd);
  EXPECT_EQ(memory[0x85ba], 0x05);
  EXPECT_EQ(memory[0xddc7], 0x04);
  EXPECT_EQ(memory[0xdec7], 0xd5);
}
TEST(CPU, instruction_LDA_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xbd";

  constexpr std::uint16_t PC = 0x3afb;
  constexpr uint8_t SP = 0x7c;
  constexpr uint8_t A = 0xce;
  constexpr uint8_t X = 0xa2;
  constexpr uint8_t Y = 0x3f;
  constexpr uint8_t P = 0xac;

  memory[0x3afb] = 0xbd;
  memory[0x3afc] = 0xa0;
  memory[0x3afd] = 0x01;
  memory[0x0142] = 0x43;
  memory[0x0242] = 0x10;
  memory[0x3afe] = 0xa3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x3afe);
  EXPECT_EQ(cpu.get_SP(), 0x7c);
  EXPECT_EQ(cpu.get_A(), 0x10);
  EXPECT_EQ(cpu.get_X(), 0xa2);
  EXPECT_EQ(cpu.get_Y(), 0x3f);
  EXPECT_EQ(cpu.get_P(), 0x2c);

  EXPECT_EQ(memory[0x0142], 0x43);
  EXPECT_EQ(memory[0x0242], 0x10);
  EXPECT_EQ(memory[0x3afb], 0xbd);
  EXPECT_EQ(memory[0x3afc], 0xa0);
  EXPECT_EQ(memory[0x3afd], 0x01);
  EXPECT_EQ(memory[0x3afe], 0xa3);
}
TEST(CPU, instruction_LDX_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xbe";

  constexpr std::uint16_t PC = 0x593e;
  constexpr uint8_t SP = 0x02;
  constexpr uint8_t A = 0x8c;
  constexpr uint8_t X = 0x03;
  constexpr uint8_t Y = 0x38;
  constexpr uint8_t P = 0x29;

  memory[0x593e] = 0xbe;
  memory[0x593f] = 0xa2;
  memory[0x5940] = 0xd6;
  memory[0xd6da] = 0x7b;
  memory[0x5941] = 0x32;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5941);
  EXPECT_EQ(cpu.get_SP(), 0x02);
  EXPECT_EQ(cpu.get_A(), 0x8c);
  EXPECT_EQ(cpu.get_X(), 0x7b);
  EXPECT_EQ(cpu.get_Y(), 0x38);
  EXPECT_EQ(cpu.get_P(), 0x29);

  EXPECT_EQ(memory[0x593e], 0xbe);
  EXPECT_EQ(memory[0x593f], 0xa2);
  EXPECT_EQ(memory[0x5940], 0xd6);
  EXPECT_EQ(memory[0x5941], 0x32);
  EXPECT_EQ(memory[0xd6da], 0x7b);
}
TEST(CPU, instruction_CPY_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc0";

  constexpr std::uint16_t PC = 0x9413;
  constexpr uint8_t SP = 0x87;
  constexpr uint8_t A = 0x1a;
  constexpr uint8_t X = 0x16;
  constexpr uint8_t Y = 0x4c;
  constexpr uint8_t P = 0x2a;

  memory[0x9413] = 0xc0;
  memory[0x9414] = 0x59;
  memory[0x9415] = 0xe4;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x9415);
  EXPECT_EQ(cpu.get_SP(), 0x87);
  EXPECT_EQ(cpu.get_A(), 0x1a);
  EXPECT_EQ(cpu.get_X(), 0x16);
  EXPECT_EQ(cpu.get_Y(), 0x4c);
  EXPECT_EQ(cpu.get_P(), 0xa8);

  EXPECT_EQ(memory[0x9413], 0xc0);
  EXPECT_EQ(memory[0x9414], 0x59);
  EXPECT_EQ(memory[0x9415], 0xe4);
}
TEST(CPU, instruction_CMP_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc1";

  constexpr std::uint16_t PC = 0xdb1d;
  constexpr uint8_t SP = 0x0e;
  constexpr uint8_t A = 0x31;
  constexpr uint8_t X = 0xe6;
  constexpr uint8_t Y = 0xd7;
  constexpr uint8_t P = 0xa4;

  memory[0xdb1d] = 0xc1;
  memory[0xdb1e] = 0xbe;
  memory[0xdb1f] = 0xb8;
  memory[0x00be] = 0xed;
  memory[0x00a4] = 0x36;
  memory[0x00a5] = 0x61;
  memory[0x6136] = 0x4a;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xdb1f);
  EXPECT_EQ(cpu.get_SP(), 0x0e);
  EXPECT_EQ(cpu.get_A(), 0x31);
  EXPECT_EQ(cpu.get_X(), 0xe6);
  EXPECT_EQ(cpu.get_Y(), 0xd7);
  EXPECT_EQ(cpu.get_P(), 0xa4);

  EXPECT_EQ(memory[0x00a4], 0x36);
  EXPECT_EQ(memory[0x00a5], 0x61);
  EXPECT_EQ(memory[0x00be], 0xed);
  EXPECT_EQ(memory[0x6136], 0x4a);
  EXPECT_EQ(memory[0xdb1d], 0xc1);
  EXPECT_EQ(memory[0xdb1e], 0xbe);
  EXPECT_EQ(memory[0xdb1f], 0xb8);
}
TEST(CPU, instruction_CPY_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc4";

  constexpr std::uint16_t PC = 0x22bf;
  constexpr uint8_t SP = 0x6e;
  constexpr uint8_t A = 0x3a;
  constexpr uint8_t X = 0xb3;
  constexpr uint8_t Y = 0x42;
  constexpr uint8_t P = 0xeb;

  memory[0x22bf] = 0xc4;
  memory[0x22c0] = 0x74;
  memory[0x22c1] = 0xd7;
  memory[0x0074] = 0xd9;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x22c1);
  EXPECT_EQ(cpu.get_SP(), 0x6e);
  EXPECT_EQ(cpu.get_A(), 0x3a);
  EXPECT_EQ(cpu.get_X(), 0xb3);
  EXPECT_EQ(cpu.get_Y(), 0x42);
  EXPECT_EQ(cpu.get_P(), 0x68);

  EXPECT_EQ(memory[0x0074], 0xd9);
  EXPECT_EQ(memory[0x22bf], 0xc4);
  EXPECT_EQ(memory[0x22c0], 0x74);
  EXPECT_EQ(memory[0x22c1], 0xd7);
}
TEST(CPU, instruction_CMP_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc5";

  constexpr std::uint16_t PC = 0xa698;
  constexpr uint8_t SP = 0xba;
  constexpr uint8_t A = 0x26;
  constexpr uint8_t X = 0x4d;
  constexpr uint8_t Y = 0x2b;
  constexpr uint8_t P = 0xe4;

  memory[0xa698] = 0xc5;
  memory[0xa699] = 0x87;
  memory[0xa69a] = 0x73;
  memory[0x0087] = 0x86;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa69a);
  EXPECT_EQ(cpu.get_SP(), 0xba);
  EXPECT_EQ(cpu.get_A(), 0x26);
  EXPECT_EQ(cpu.get_X(), 0x4d);
  EXPECT_EQ(cpu.get_Y(), 0x2b);
  EXPECT_EQ(cpu.get_P(), 0xe4);

  EXPECT_EQ(memory[0x0087], 0x86);
  EXPECT_EQ(memory[0xa698], 0xc5);
  EXPECT_EQ(memory[0xa699], 0x87);
  EXPECT_EQ(memory[0xa69a], 0x73);
}
TEST(CPU, instruction_DEC_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc6";

  constexpr std::uint16_t PC = 0x034a;
  constexpr uint8_t SP = 0x4e;
  constexpr uint8_t A = 0x40;
  constexpr uint8_t X = 0x3c;
  constexpr uint8_t Y = 0x4c;
  constexpr uint8_t P = 0xe7;

  memory[0x034a] = 0xc6;
  memory[0x034b] = 0x4b;
  memory[0x034c] = 0xee;
  memory[0x004b] = 0xf7;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x034c);
  EXPECT_EQ(cpu.get_SP(), 0x4e);
  EXPECT_EQ(cpu.get_A(), 0x40);
  EXPECT_EQ(cpu.get_X(), 0x3c);
  EXPECT_EQ(cpu.get_Y(), 0x4c);
  EXPECT_EQ(cpu.get_P(), 0xe5);

  EXPECT_EQ(memory[0x004b], 0xf6);
  EXPECT_EQ(memory[0x034a], 0xc6);
  EXPECT_EQ(memory[0x034b], 0x4b);
  EXPECT_EQ(memory[0x034c], 0xee);
}
TEST(CPU, instruction_INY_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc8";

  constexpr std::uint16_t PC = 0x0917;
  constexpr uint8_t SP = 0xd9;
  constexpr uint8_t A = 0x6e;
  constexpr uint8_t X = 0x2d;
  constexpr uint8_t Y = 0x31;
  constexpr uint8_t P = 0x6e;

  memory[0x0917] = 0xc8;
  memory[0x0918] = 0x45;
  memory[0x0919] = 0x64;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0918);
  EXPECT_EQ(cpu.get_SP(), 0xd9);
  EXPECT_EQ(cpu.get_A(), 0x6e);
  EXPECT_EQ(cpu.get_X(), 0x2d);
  EXPECT_EQ(cpu.get_Y(), 0x32);
  EXPECT_EQ(cpu.get_P(), 0x6c);

  EXPECT_EQ(memory[0x0917], 0xc8);
  EXPECT_EQ(memory[0x0918], 0x45);
  EXPECT_EQ(memory[0x0919], 0x64);
}
TEST(CPU, instruction_CMP_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xc9";

  constexpr std::uint16_t PC = 0x5b8c;
  constexpr uint8_t SP = 0xb6;
  constexpr uint8_t A = 0x10;
  constexpr uint8_t X = 0xf2;
  constexpr uint8_t Y = 0x13;
  constexpr uint8_t P = 0xaf;

  memory[0x5b8c] = 0xc9;
  memory[0x5b8d] = 0xbb;
  memory[0x5b8e] = 0xbf;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5b8e);
  EXPECT_EQ(cpu.get_SP(), 0xb6);
  EXPECT_EQ(cpu.get_A(), 0x10);
  EXPECT_EQ(cpu.get_X(), 0xf2);
  EXPECT_EQ(cpu.get_Y(), 0x13);
  EXPECT_EQ(cpu.get_P(), 0x2c);

  EXPECT_EQ(memory[0x5b8c], 0xc9);
  EXPECT_EQ(memory[0x5b8d], 0xbb);
  EXPECT_EQ(memory[0x5b8e], 0xbf);
}
TEST(CPU, instruction_DEX_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xca";

  constexpr std::uint16_t PC = 0x7b8f;
  constexpr uint8_t SP = 0xf4;
  constexpr uint8_t A = 0xc8;
  constexpr uint8_t X = 0x03;
  constexpr uint8_t Y = 0x78;
  constexpr uint8_t P = 0xa4;

  memory[0x7b8f] = 0xca;
  memory[0x7b90] = 0x62;
  memory[0x7b91] = 0x35;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x7b90);
  EXPECT_EQ(cpu.get_SP(), 0xf4);
  EXPECT_EQ(cpu.get_A(), 0xc8);
  EXPECT_EQ(cpu.get_X(), 0x02);
  EXPECT_EQ(cpu.get_Y(), 0x78);
  EXPECT_EQ(cpu.get_P(), 0x24);

  EXPECT_EQ(memory[0x7b8f], 0xca);
  EXPECT_EQ(memory[0x7b90], 0x62);
  EXPECT_EQ(memory[0x7b91], 0x35);
}
TEST(CPU, instruction_CPY_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xcc";

  constexpr std::uint16_t PC = 0xcd48;
  constexpr uint8_t SP = 0x06;
  constexpr uint8_t A = 0x3d;
  constexpr uint8_t X = 0xc4;
  constexpr uint8_t Y = 0x00;
  constexpr uint8_t P = 0x2d;

  memory[0xcd48] = 0xcc;
  memory[0xcd49] = 0xb3;
  memory[0xcd4a] = 0x2c;
  memory[0x2cb3] = 0xe9;
  memory[0xcd4b] = 0x01;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xcd4b);
  EXPECT_EQ(cpu.get_SP(), 0x06);
  EXPECT_EQ(cpu.get_A(), 0x3d);
  EXPECT_EQ(cpu.get_X(), 0xc4);
  EXPECT_EQ(cpu.get_Y(), 0x00);
  EXPECT_EQ(cpu.get_P(), 0x2c);

  EXPECT_EQ(memory[0x2cb3], 0xe9);
  EXPECT_EQ(memory[0xcd48], 0xcc);
  EXPECT_EQ(memory[0xcd49], 0xb3);
  EXPECT_EQ(memory[0xcd4a], 0x2c);
  EXPECT_EQ(memory[0xcd4b], 0x01);
}
TEST(CPU, instruction_CMP_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xcd";

  constexpr std::uint16_t PC = 0xdf0b;
  constexpr uint8_t SP = 0xfd;
  constexpr uint8_t A = 0x88;
  constexpr uint8_t X = 0xdc;
  constexpr uint8_t Y = 0xc3;
  constexpr uint8_t P = 0xe8;

  memory[0xdf0b] = 0xcd;
  memory[0xdf0c] = 0x0a;
  memory[0xdf0d] = 0x26;
  memory[0x260a] = 0x35;
  memory[0xdf0e] = 0x26;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xdf0e);
  EXPECT_EQ(cpu.get_SP(), 0xfd);
  EXPECT_EQ(cpu.get_A(), 0x88);
  EXPECT_EQ(cpu.get_X(), 0xdc);
  EXPECT_EQ(cpu.get_Y(), 0xc3);
  EXPECT_EQ(cpu.get_P(), 0x69);

  EXPECT_EQ(memory[0x260a], 0x35);
  EXPECT_EQ(memory[0xdf0b], 0xcd);
  EXPECT_EQ(memory[0xdf0c], 0x0a);
  EXPECT_EQ(memory[0xdf0d], 0x26);
  EXPECT_EQ(memory[0xdf0e], 0x26);
}
TEST(CPU, instruction_DEC_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xce";

  constexpr std::uint16_t PC = 0xc7e9;
  constexpr uint8_t SP = 0x42;
  constexpr uint8_t A = 0xa6;
  constexpr uint8_t X = 0xf4;
  constexpr uint8_t Y = 0x2c;
  constexpr uint8_t P = 0x6c;

  memory[0xc7e9] = 0xce;
  memory[0xc7ea] = 0x67;
  memory[0xc7eb] = 0x9d;
  memory[0x9d67] = 0x18;
  memory[0xc7ec] = 0xe4;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xc7ec);
  EXPECT_EQ(cpu.get_SP(), 0x42);
  EXPECT_EQ(cpu.get_A(), 0xa6);
  EXPECT_EQ(cpu.get_X(), 0xf4);
  EXPECT_EQ(cpu.get_Y(), 0x2c);
  EXPECT_EQ(cpu.get_P(), 0x6c);

  EXPECT_EQ(memory[0x9d67], 0x17);
  EXPECT_EQ(memory[0xc7e9], 0xce);
  EXPECT_EQ(memory[0xc7ea], 0x67);
  EXPECT_EQ(memory[0xc7eb], 0x9d);
  EXPECT_EQ(memory[0xc7ec], 0xe4);
}
TEST(CPU, instruction_BNE_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xd0";

  constexpr std::uint16_t PC = 0x40dc;
  constexpr uint8_t SP = 0x8b;
  constexpr uint8_t A = 0x21;
  constexpr uint8_t X = 0xcc;
  constexpr uint8_t Y = 0xd7;
  constexpr uint8_t P = 0xec;

  memory[0x40dc] = 0xd0;
  memory[0x40dd] = 0x2b;
  memory[0x40de] = 0x3a;
  memory[0x4009] = 0xc1;
  memory[0x4109] = 0x62;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4109);
  EXPECT_EQ(cpu.get_SP(), 0x8b);
  EXPECT_EQ(cpu.get_A(), 0x21);
  EXPECT_EQ(cpu.get_X(), 0xcc);
  EXPECT_EQ(cpu.get_Y(), 0xd7);
  EXPECT_EQ(cpu.get_P(), 0xec);

  EXPECT_EQ(memory[0x4009], 0xc1);
  EXPECT_EQ(memory[0x40dc], 0xd0);
  EXPECT_EQ(memory[0x40dd], 0x2b);
  EXPECT_EQ(memory[0x40de], 0x3a);
  EXPECT_EQ(memory[0x4109], 0x62);
}
TEST(CPU, instruction_CMP_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xd1";

  constexpr std::uint16_t PC = 0x256d;
  constexpr uint8_t SP = 0xa6;
  constexpr uint8_t A = 0x6a;
  constexpr uint8_t X = 0x0f;
  constexpr uint8_t Y = 0x7f;
  constexpr uint8_t P = 0x29;

  memory[0x256d] = 0xd1;
  memory[0x256e] = 0x14;
  memory[0x256f] = 0x29;
  memory[0x0014] = 0x6e;
  memory[0x0015] = 0x4b;
  memory[0x4bed] = 0xae;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x256f);
  EXPECT_EQ(cpu.get_SP(), 0xa6);
  EXPECT_EQ(cpu.get_A(), 0x6a);
  EXPECT_EQ(cpu.get_X(), 0x0f);
  EXPECT_EQ(cpu.get_Y(), 0x7f);
  EXPECT_EQ(cpu.get_P(), 0xa8);

  EXPECT_EQ(memory[0x0014], 0x6e);
  EXPECT_EQ(memory[0x0015], 0x4b);
  EXPECT_EQ(memory[0x256d], 0xd1);
  EXPECT_EQ(memory[0x256e], 0x14);
  EXPECT_EQ(memory[0x256f], 0x29);
  EXPECT_EQ(memory[0x4bed], 0xae);
}
TEST(CPU, instruction_CMP_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xd5";

  constexpr std::uint16_t PC = 0xbee6;
  constexpr uint8_t SP = 0x0a;
  constexpr uint8_t A = 0x47;
  constexpr uint8_t X = 0xbd;
  constexpr uint8_t Y = 0xc2;
  constexpr uint8_t P = 0x2f;

  memory[0xbee6] = 0xd5;
  memory[0xbee7] = 0x27;
  memory[0xbee8] = 0xa1;
  memory[0x0027] = 0x26;
  memory[0x00e4] = 0xa1;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xbee8);
  EXPECT_EQ(cpu.get_SP(), 0x0a);
  EXPECT_EQ(cpu.get_A(), 0x47);
  EXPECT_EQ(cpu.get_X(), 0xbd);
  EXPECT_EQ(cpu.get_Y(), 0xc2);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x0027], 0x26);
  EXPECT_EQ(memory[0x00e4], 0xa1);
  EXPECT_EQ(memory[0xbee6], 0xd5);
  EXPECT_EQ(memory[0xbee7], 0x27);
  EXPECT_EQ(memory[0xbee8], 0xa1);
}
TEST(CPU, instruction_DEC_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xd6";

  constexpr std::uint16_t PC = 0x82ee;
  constexpr uint8_t SP = 0x6f;
  constexpr uint8_t A = 0x1a;
  constexpr uint8_t X = 0x28;
  constexpr uint8_t Y = 0x09;
  constexpr uint8_t P = 0xac;

  memory[0x82ee] = 0xd6;
  memory[0x82ef] = 0xbe;
  memory[0x82f0] = 0xed;
  memory[0x00be] = 0x1f;
  memory[0x00e6] = 0xb9;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x82f0);
  EXPECT_EQ(cpu.get_SP(), 0x6f);
  EXPECT_EQ(cpu.get_A(), 0x1a);
  EXPECT_EQ(cpu.get_X(), 0x28);
  EXPECT_EQ(cpu.get_Y(), 0x09);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x00be], 0x1f);
  EXPECT_EQ(memory[0x00e6], 0xb8);
  EXPECT_EQ(memory[0x82ee], 0xd6);
  EXPECT_EQ(memory[0x82ef], 0xbe);
  EXPECT_EQ(memory[0x82f0], 0xed);
}
TEST(CPU, instruction_CLD_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xd8";

  constexpr std::uint16_t PC = 0x240c;
  constexpr uint8_t SP = 0xfa;
  constexpr uint8_t A = 0x4f;
  constexpr uint8_t X = 0x50;
  constexpr uint8_t Y = 0xc4;
  constexpr uint8_t P = 0x22;

  memory[0x240c] = 0xd8;
  memory[0x240d] = 0x80;
  memory[0x240e] = 0x34;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x240d);
  EXPECT_EQ(cpu.get_SP(), 0xfa);
  EXPECT_EQ(cpu.get_A(), 0x4f);
  EXPECT_EQ(cpu.get_X(), 0x50);
  EXPECT_EQ(cpu.get_Y(), 0xc4);
  EXPECT_EQ(cpu.get_P(), 0x22);

  EXPECT_EQ(memory[0x240c], 0xd8);
  EXPECT_EQ(memory[0x240d], 0x80);
  EXPECT_EQ(memory[0x240e], 0x34);
}
TEST(CPU, instruction_CMP_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xd9";

  constexpr std::uint16_t PC = 0x164e;
  constexpr uint8_t SP = 0xd9;
  constexpr uint8_t A = 0xfe;
  constexpr uint8_t X = 0x37;
  constexpr uint8_t Y = 0x5e;
  constexpr uint8_t P = 0x27;

  memory[0x164e] = 0xd9;
  memory[0x164f] = 0x94;
  memory[0x1650] = 0x3b;
  memory[0x3bf2] = 0xfd;
  memory[0x1651] = 0x09;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x1651);
  EXPECT_EQ(cpu.get_SP(), 0xd9);
  EXPECT_EQ(cpu.get_A(), 0xfe);
  EXPECT_EQ(cpu.get_X(), 0x37);
  EXPECT_EQ(cpu.get_Y(), 0x5e);
  EXPECT_EQ(cpu.get_P(), 0x25);

  EXPECT_EQ(memory[0x164e], 0xd9);
  EXPECT_EQ(memory[0x164f], 0x94);
  EXPECT_EQ(memory[0x1650], 0x3b);
  EXPECT_EQ(memory[0x1651], 0x09);
  EXPECT_EQ(memory[0x3bf2], 0xfd);
}
TEST(CPU, instruction_CMP_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xdd";

  constexpr std::uint16_t PC = 0x1fc2;
  constexpr uint8_t SP = 0x92;
  constexpr uint8_t A = 0x7f;
  constexpr uint8_t X = 0xbc;
  constexpr uint8_t Y = 0x24;
  constexpr uint8_t P = 0xa8;

  memory[0x1fc2] = 0xdd;
  memory[0x1fc3] = 0x51;
  memory[0x1fc4] = 0x92;
  memory[0x920d] = 0x3a;
  memory[0x930d] = 0xac;
  memory[0x1fc5] = 0x53;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x1fc5);
  EXPECT_EQ(cpu.get_SP(), 0x92);
  EXPECT_EQ(cpu.get_A(), 0x7f);
  EXPECT_EQ(cpu.get_X(), 0xbc);
  EXPECT_EQ(cpu.get_Y(), 0x24);
  EXPECT_EQ(cpu.get_P(), 0xa8);

  EXPECT_EQ(memory[0x1fc2], 0xdd);
  EXPECT_EQ(memory[0x1fc3], 0x51);
  EXPECT_EQ(memory[0x1fc4], 0x92);
  EXPECT_EQ(memory[0x1fc5], 0x53);
  EXPECT_EQ(memory[0x920d], 0x3a);
  EXPECT_EQ(memory[0x930d], 0xac);
}
TEST(CPU, instruction_DEC_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xde";

  constexpr std::uint16_t PC = 0xf28d;
  constexpr uint8_t SP = 0xea;
  constexpr uint8_t A = 0x79;
  constexpr uint8_t X = 0x8b;
  constexpr uint8_t Y = 0xc0;
  constexpr uint8_t P = 0x26;

  memory[0xf28d] = 0xde;
  memory[0xf28e] = 0x0e;
  memory[0xf28f] = 0x74;
  memory[0x7499] = 0xbe;
  memory[0xf290] = 0x5c;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xf290);
  EXPECT_EQ(cpu.get_SP(), 0xea);
  EXPECT_EQ(cpu.get_A(), 0x79);
  EXPECT_EQ(cpu.get_X(), 0x8b);
  EXPECT_EQ(cpu.get_Y(), 0xc0);
  EXPECT_EQ(cpu.get_P(), 0xa4);

  EXPECT_EQ(memory[0x7499], 0xbd);
  EXPECT_EQ(memory[0xf28d], 0xde);
  EXPECT_EQ(memory[0xf28e], 0x0e);
  EXPECT_EQ(memory[0xf28f], 0x74);
  EXPECT_EQ(memory[0xf290], 0x5c);
}
TEST(CPU, instruction_CPX_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe0";

  constexpr std::uint16_t PC = 0x2ec1;
  constexpr uint8_t SP = 0x03;
  constexpr uint8_t A = 0xee;
  constexpr uint8_t X = 0xf8;
  constexpr uint8_t Y = 0x31;
  constexpr uint8_t P = 0xa9;

  memory[0x2ec1] = 0xe0;
  memory[0x2ec2] = 0x1c;
  memory[0x2ec3] = 0xac;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x2ec3);
  EXPECT_EQ(cpu.get_SP(), 0x03);
  EXPECT_EQ(cpu.get_A(), 0xee);
  EXPECT_EQ(cpu.get_X(), 0xf8);
  EXPECT_EQ(cpu.get_Y(), 0x31);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x2ec1], 0xe0);
  EXPECT_EQ(memory[0x2ec2], 0x1c);
  EXPECT_EQ(memory[0x2ec3], 0xac);
}
TEST(CPU, instruction_SBC_indirect_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe1";

  constexpr std::uint16_t PC = 0xa727;
  constexpr uint8_t SP = 0xdf;
  constexpr uint8_t A = 0xad;
  constexpr uint8_t X = 0x1c;
  constexpr uint8_t Y = 0xf0;
  constexpr uint8_t P = 0xa1;

  memory[0xa727] = 0xe1;
  memory[0xa728] = 0xa5;
  memory[0xa729] = 0x44;
  memory[0x00a5] = 0xdb;
  memory[0x00c1] = 0x6e;
  memory[0x00c2] = 0xcd;
  memory[0xcd6e] = 0x73;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa729);
  EXPECT_EQ(cpu.get_SP(), 0xdf);
  EXPECT_EQ(cpu.get_A(), 0x3a);
  EXPECT_EQ(cpu.get_X(), 0x1c);
  EXPECT_EQ(cpu.get_Y(), 0xf0);
  EXPECT_EQ(cpu.get_P(), 0x61);

  EXPECT_EQ(memory[0x00a5], 0xdb);
  EXPECT_EQ(memory[0x00c1], 0x6e);
  EXPECT_EQ(memory[0x00c2], 0xcd);
  EXPECT_EQ(memory[0xa727], 0xe1);
  EXPECT_EQ(memory[0xa728], 0xa5);
  EXPECT_EQ(memory[0xa729], 0x44);
  EXPECT_EQ(memory[0xcd6e], 0x73);
}
TEST(CPU, instruction_CPX_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe4";

  constexpr std::uint16_t PC = 0x4f7b;
  constexpr uint8_t SP = 0xfc;
  constexpr uint8_t A = 0x24;
  constexpr uint8_t X = 0xb1;
  constexpr uint8_t Y = 0xfa;
  constexpr uint8_t P = 0xa8;

  memory[0x4f7b] = 0xe4;
  memory[0x4f7c] = 0xb8;
  memory[0x4f7d] = 0xa1;
  memory[0x00b8] = 0x0b;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x4f7d);
  EXPECT_EQ(cpu.get_SP(), 0xfc);
  EXPECT_EQ(cpu.get_A(), 0x24);
  EXPECT_EQ(cpu.get_X(), 0xb1);
  EXPECT_EQ(cpu.get_Y(), 0xfa);
  EXPECT_EQ(cpu.get_P(), 0xa9);

  EXPECT_EQ(memory[0x00b8], 0x0b);
  EXPECT_EQ(memory[0x4f7b], 0xe4);
  EXPECT_EQ(memory[0x4f7c], 0xb8);
  EXPECT_EQ(memory[0x4f7d], 0xa1);
}
TEST(CPU, instruction_SBC_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe5";

  constexpr std::uint16_t PC = 0x22fd;
  constexpr uint8_t SP = 0xf0;
  constexpr uint8_t A = 0xe0;
  constexpr uint8_t X = 0x75;
  constexpr uint8_t Y = 0x53;
  constexpr uint8_t P = 0xa4;

  memory[0x22fd] = 0xe5;
  memory[0x22fe] = 0xfa;
  memory[0x22ff] = 0x1e;
  memory[0x00fa] = 0x00;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x22ff);
  EXPECT_EQ(cpu.get_SP(), 0xf0);
  EXPECT_EQ(cpu.get_A(), 0xdf);
  EXPECT_EQ(cpu.get_X(), 0x75);
  EXPECT_EQ(cpu.get_Y(), 0x53);
  EXPECT_EQ(cpu.get_P(), 0xa5);

  EXPECT_EQ(memory[0x00fa], 0x00);
  EXPECT_EQ(memory[0x22fd], 0xe5);
  EXPECT_EQ(memory[0x22fe], 0xfa);
  EXPECT_EQ(memory[0x22ff], 0x1e);
}
TEST(CPU, instruction_INC_zero_page) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe6";

  constexpr std::uint16_t PC = 0xa3bf;
  constexpr uint8_t SP = 0x12;
  constexpr uint8_t A = 0x00;
  constexpr uint8_t X = 0xc2;
  constexpr uint8_t Y = 0x77;
  constexpr uint8_t P = 0x2e;

  memory[0xa3bf] = 0xe6;
  memory[0xa3c0] = 0xe4;
  memory[0xa3c1] = 0x2d;
  memory[0x00e4] = 0xc9;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa3c1);
  EXPECT_EQ(cpu.get_SP(), 0x12);
  EXPECT_EQ(cpu.get_A(), 0x00);
  EXPECT_EQ(cpu.get_X(), 0xc2);
  EXPECT_EQ(cpu.get_Y(), 0x77);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x00e4], 0xca);
  EXPECT_EQ(memory[0xa3bf], 0xe6);
  EXPECT_EQ(memory[0xa3c0], 0xe4);
  EXPECT_EQ(memory[0xa3c1], 0x2d);
}
TEST(CPU, instruction_INX_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe8";

  constexpr std::uint16_t PC = 0x5cb6;
  constexpr uint8_t SP = 0x9c;
  constexpr uint8_t A = 0x85;
  constexpr uint8_t X = 0x4b;
  constexpr uint8_t Y = 0x55;
  constexpr uint8_t P = 0x60;

  memory[0x5cb6] = 0xe8;
  memory[0x5cb7] = 0xfc;
  memory[0x5cb8] = 0xd3;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5cb7);
  EXPECT_EQ(cpu.get_SP(), 0x9c);
  EXPECT_EQ(cpu.get_A(), 0x85);
  EXPECT_EQ(cpu.get_X(), 0x4c);
  EXPECT_EQ(cpu.get_Y(), 0x55);
  EXPECT_EQ(cpu.get_P(), 0x60);

  EXPECT_EQ(memory[0x5cb6], 0xe8);
  EXPECT_EQ(memory[0x5cb7], 0xfc);
  EXPECT_EQ(memory[0x5cb8], 0xd3);
}
TEST(CPU, instruction_SBC_immediate) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xe9";

  constexpr std::uint16_t PC = 0x0084;
  constexpr uint8_t SP = 0x26;
  constexpr uint8_t A = 0x9c;
  constexpr uint8_t X = 0x72;
  constexpr uint8_t Y = 0xcc;
  constexpr uint8_t P = 0x6d;

  memory[0x0084] = 0xe9;
  memory[0x0085] = 0xc4;
  memory[0x0086] = 0x08;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x0086);
  EXPECT_EQ(cpu.get_SP(), 0x26);
  EXPECT_EQ(cpu.get_A(), 0x78);
  EXPECT_EQ(cpu.get_X(), 0x72);
  EXPECT_EQ(cpu.get_Y(), 0xcc);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x0084], 0xe9);
  EXPECT_EQ(memory[0x0085], 0xc4);
  EXPECT_EQ(memory[0x0086], 0x08);
}
TEST(CPU, instruction_CPX_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xec";

  constexpr std::uint16_t PC = 0x9bb4;
  constexpr uint8_t SP = 0x9c;
  constexpr uint8_t A = 0xcb;
  constexpr uint8_t X = 0xac;
  constexpr uint8_t Y = 0x56;
  constexpr uint8_t P = 0xad;

  memory[0x9bb4] = 0xec;
  memory[0x9bb5] = 0x54;
  memory[0x9bb6] = 0x9d;
  memory[0x9d54] = 0xef;
  memory[0x9bb7] = 0xbd;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x9bb7);
  EXPECT_EQ(cpu.get_SP(), 0x9c);
  EXPECT_EQ(cpu.get_A(), 0xcb);
  EXPECT_EQ(cpu.get_X(), 0xac);
  EXPECT_EQ(cpu.get_Y(), 0x56);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x9bb4], 0xec);
  EXPECT_EQ(memory[0x9bb5], 0x54);
  EXPECT_EQ(memory[0x9bb6], 0x9d);
  EXPECT_EQ(memory[0x9bb7], 0xbd);
  EXPECT_EQ(memory[0x9d54], 0xef);
}
TEST(CPU, instruction_SBC_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xed";

  constexpr std::uint16_t PC = 0x5f06;
  constexpr uint8_t SP = 0x99;
  constexpr uint8_t A = 0x87;
  constexpr uint8_t X = 0x79;
  constexpr uint8_t Y = 0x5c;
  constexpr uint8_t P = 0xec;

  memory[0x5f06] = 0xed;
  memory[0x5f07] = 0xee;
  memory[0x5f08] = 0x4f;
  memory[0x4fee] = 0xf9;
  memory[0x5f09] = 0xa0;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5f09);
  EXPECT_EQ(cpu.get_SP(), 0x99);
  EXPECT_EQ(cpu.get_A(), 0x27);
  EXPECT_EQ(cpu.get_X(), 0x79);
  EXPECT_EQ(cpu.get_Y(), 0x5c);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x4fee], 0xf9);
  EXPECT_EQ(memory[0x5f06], 0xed);
  EXPECT_EQ(memory[0x5f07], 0xee);
  EXPECT_EQ(memory[0x5f08], 0x4f);
  EXPECT_EQ(memory[0x5f09], 0xa0);
}
TEST(CPU, instruction_INC_absolute) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xee";

  constexpr std::uint16_t PC = 0xa3cc;
  constexpr uint8_t SP = 0xa1;
  constexpr uint8_t A = 0x8a;
  constexpr uint8_t X = 0xe9;
  constexpr uint8_t Y = 0xda;
  constexpr uint8_t P = 0x6b;

  memory[0xa3cc] = 0xee;
  memory[0xa3cd] = 0x8f;
  memory[0xa3ce] = 0x74;
  memory[0x748f] = 0x9a;
  memory[0xa3cf] = 0x44;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xa3cf);
  EXPECT_EQ(cpu.get_SP(), 0xa1);
  EXPECT_EQ(cpu.get_A(), 0x8a);
  EXPECT_EQ(cpu.get_X(), 0xe9);
  EXPECT_EQ(cpu.get_Y(), 0xda);
  EXPECT_EQ(cpu.get_P(), 0xe9);

  EXPECT_EQ(memory[0x748f], 0x9b);
  EXPECT_EQ(memory[0xa3cc], 0xee);
  EXPECT_EQ(memory[0xa3cd], 0x8f);
  EXPECT_EQ(memory[0xa3ce], 0x74);
  EXPECT_EQ(memory[0xa3cf], 0x44);
}
TEST(CPU, instruction_BEQ_relative) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xf0";

  constexpr std::uint16_t PC = 0xe3c8;
  constexpr uint8_t SP = 0x89;
  constexpr uint8_t A = 0x55;
  constexpr uint8_t X = 0xff;
  constexpr uint8_t Y = 0x96;
  constexpr uint8_t P = 0x65;

  memory[0xe3c8] = 0xf0;
  memory[0xe3c9] = 0x34;
  memory[0xe3ca] = 0x4e;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xe3ca);
  EXPECT_EQ(cpu.get_SP(), 0x89);
  EXPECT_EQ(cpu.get_A(), 0x55);
  EXPECT_EQ(cpu.get_X(), 0xff);
  EXPECT_EQ(cpu.get_Y(), 0x96);
  EXPECT_EQ(cpu.get_P(), 0x65);

  EXPECT_EQ(memory[0xe3c8], 0xf0);
  EXPECT_EQ(memory[0xe3c9], 0x34);
  EXPECT_EQ(memory[0xe3ca], 0x4e);
}
TEST(CPU, instruction_SBC_indirect_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xf1";

  constexpr std::uint16_t PC = 0x6198;
  constexpr uint8_t SP = 0x4b;
  constexpr uint8_t A = 0x4e;
  constexpr uint8_t X = 0x2d;
  constexpr uint8_t Y = 0xe0;
  constexpr uint8_t P = 0x22;

  memory[0x6198] = 0xf1;
  memory[0x6199] = 0x19;
  memory[0x619a] = 0x13;
  memory[0x0019] = 0xde;
  memory[0x001a] = 0x15;
  memory[0x15be] = 0x24;
  memory[0x16be] = 0xe5;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x619a);
  EXPECT_EQ(cpu.get_SP(), 0x4b);
  EXPECT_EQ(cpu.get_A(), 0x68);
  EXPECT_EQ(cpu.get_X(), 0x2d);
  EXPECT_EQ(cpu.get_Y(), 0xe0);
  EXPECT_EQ(cpu.get_P(), 0x20);

  EXPECT_EQ(memory[0x0019], 0xde);
  EXPECT_EQ(memory[0x001a], 0x15);
  EXPECT_EQ(memory[0x15be], 0x24);
  EXPECT_EQ(memory[0x16be], 0xe5);
  EXPECT_EQ(memory[0x6198], 0xf1);
  EXPECT_EQ(memory[0x6199], 0x19);
  EXPECT_EQ(memory[0x619a], 0x13);
}
TEST(CPU, instruction_SBC_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xf5";

  constexpr std::uint16_t PC = 0x551f;
  constexpr uint8_t SP = 0xb7;
  constexpr uint8_t A = 0x08;
  constexpr uint8_t X = 0x6c;
  constexpr uint8_t Y = 0xc3;
  constexpr uint8_t P = 0x2f;

  memory[0x551f] = 0xf5;
  memory[0x5520] = 0xdd;
  memory[0x5521] = 0x8e;
  memory[0x00dd] = 0xe6;
  memory[0x0049] = 0x25;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x5521);
  EXPECT_EQ(cpu.get_SP(), 0xb7);
  EXPECT_EQ(cpu.get_A(), 0x83);
  EXPECT_EQ(cpu.get_X(), 0x6c);
  EXPECT_EQ(cpu.get_Y(), 0xc3);
  EXPECT_EQ(cpu.get_P(), 0xac);

  EXPECT_EQ(memory[0x0049], 0x25);
  EXPECT_EQ(memory[0x00dd], 0xe6);
  EXPECT_EQ(memory[0x551f], 0xf5);
  EXPECT_EQ(memory[0x5520], 0xdd);
  EXPECT_EQ(memory[0x5521], 0x8e);
}
TEST(CPU, instruction_INC_zero_page_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xf6";

  constexpr std::uint16_t PC = 0x84e6;
  constexpr uint8_t SP = 0x3c;
  constexpr uint8_t A = 0x29;
  constexpr uint8_t X = 0x21;
  constexpr uint8_t Y = 0x82;
  constexpr uint8_t P = 0xe1;

  memory[0x84e6] = 0xf6;
  memory[0x84e7] = 0x6e;
  memory[0x84e8] = 0x14;
  memory[0x006e] = 0xb9;
  memory[0x008f] = 0x33;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x84e8);
  EXPECT_EQ(cpu.get_SP(), 0x3c);
  EXPECT_EQ(cpu.get_A(), 0x29);
  EXPECT_EQ(cpu.get_X(), 0x21);
  EXPECT_EQ(cpu.get_Y(), 0x82);
  EXPECT_EQ(cpu.get_P(), 0x61);

  EXPECT_EQ(memory[0x006e], 0xb9);
  EXPECT_EQ(memory[0x008f], 0x34);
  EXPECT_EQ(memory[0x84e6], 0xf6);
  EXPECT_EQ(memory[0x84e7], 0x6e);
  EXPECT_EQ(memory[0x84e8], 0x14);
}
TEST(CPU, instruction_SED_implied) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xf8";

  constexpr std::uint16_t PC = 0x386c;
  constexpr uint8_t SP = 0xbc;
  constexpr uint8_t A = 0x19;
  constexpr uint8_t X = 0xb1;
  constexpr uint8_t Y = 0x1a;
  constexpr uint8_t P = 0x28;

  memory[0x386c] = 0xf8;
  memory[0x386d] = 0x87;
  memory[0x386e] = 0x7a;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x386d);
  EXPECT_EQ(cpu.get_SP(), 0xbc);
  EXPECT_EQ(cpu.get_A(), 0x19);
  EXPECT_EQ(cpu.get_X(), 0xb1);
  EXPECT_EQ(cpu.get_Y(), 0x1a);
  EXPECT_EQ(cpu.get_P(), 0x28);

  EXPECT_EQ(memory[0x386c], 0xf8);
  EXPECT_EQ(memory[0x386d], 0x87);
  EXPECT_EQ(memory[0x386e], 0x7a);
}
TEST(CPU, instruction_SBC_absolute_y) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xf9";

  constexpr std::uint16_t PC = 0x1915;
  constexpr uint8_t SP = 0x9f;
  constexpr uint8_t A = 0xfb;
  constexpr uint8_t X = 0xff;
  constexpr uint8_t Y = 0xa7;
  constexpr uint8_t P = 0x65;

  memory[0x1915] = 0xf9;
  memory[0x1916] = 0x98;
  memory[0x1917] = 0x76;
  memory[0x763f] = 0x4c;
  memory[0x773f] = 0xbc;
  memory[0x1918] = 0x09;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x1918);
  EXPECT_EQ(cpu.get_SP(), 0x9f);
  EXPECT_EQ(cpu.get_A(), 0x3f);
  EXPECT_EQ(cpu.get_X(), 0xff);
  EXPECT_EQ(cpu.get_Y(), 0xa7);
  EXPECT_EQ(cpu.get_P(), 0x25);

  EXPECT_EQ(memory[0x1915], 0xf9);
  EXPECT_EQ(memory[0x1916], 0x98);
  EXPECT_EQ(memory[0x1917], 0x76);
  EXPECT_EQ(memory[0x1918], 0x09);
  EXPECT_EQ(memory[0x763f], 0x4c);
  EXPECT_EQ(memory[0x773f], 0xbc);
}
TEST(CPU, instruction_SBC_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xfd";

  constexpr std::uint16_t PC = 0xd5d2;
  constexpr uint8_t SP = 0xf1;
  constexpr uint8_t A = 0xeb;
  constexpr uint8_t X = 0xb0;
  constexpr uint8_t Y = 0x7b;
  constexpr uint8_t P = 0x6a;

  memory[0xd5d2] = 0xfd;
  memory[0xd5d3] = 0xfa;
  memory[0xd5d4] = 0x94;
  memory[0x94aa] = 0x1a;
  memory[0x95aa] = 0x6e;
  memory[0xd5d5] = 0x3e;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0xd5d5);
  EXPECT_EQ(cpu.get_SP(), 0xf1);
  EXPECT_EQ(cpu.get_A(), 0x76);
  EXPECT_EQ(cpu.get_X(), 0xb0);
  EXPECT_EQ(cpu.get_Y(), 0x7b);
  EXPECT_EQ(cpu.get_P(), 0x69);

  EXPECT_EQ(memory[0x94aa], 0x1a);
  EXPECT_EQ(memory[0x95aa], 0x6e);
  EXPECT_EQ(memory[0xd5d2], 0xfd);
  EXPECT_EQ(memory[0xd5d3], 0xfa);
  EXPECT_EQ(memory[0xd5d4], 0x94);
  EXPECT_EQ(memory[0xd5d5], 0x3e);
}
TEST(CPU, instruction_INC_absolute_x) {
  std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
  GTEST_SKIP() << "Skipping test for opcode 0xfe";

  constexpr std::uint16_t PC = 0x7db1;
  constexpr uint8_t SP = 0x6b;
  constexpr uint8_t A = 0x18;
  constexpr uint8_t X = 0x25;
  constexpr uint8_t Y = 0x47;
  constexpr uint8_t P = 0x6a;

  memory[0x7db1] = 0xfe;
  memory[0x7db2] = 0x7c;
  memory[0x7db3] = 0xff;
  memory[0xffa1] = 0x13;
  memory[0x7db4] = 0xe5;

  CPU::CPU cpu{memory, PC, SP, A, X, Y, P};

  cpu.run();

  EXPECT_EQ(cpu.get_PC(), 0x7db4);
  EXPECT_EQ(cpu.get_SP(), 0x6b);
  EXPECT_EQ(cpu.get_A(), 0x18);
  EXPECT_EQ(cpu.get_X(), 0x25);
  EXPECT_EQ(cpu.get_Y(), 0x47);
  EXPECT_EQ(cpu.get_P(), 0x68);

  EXPECT_EQ(memory[0x7db1], 0xfe);
  EXPECT_EQ(memory[0x7db2], 0x7c);
  EXPECT_EQ(memory[0x7db3], 0xff);
  EXPECT_EQ(memory[0x7db4], 0xe5);
  EXPECT_EQ(memory[0xffa1], 0x14);
}
