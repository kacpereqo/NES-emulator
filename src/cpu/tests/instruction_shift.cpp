// //
// // Created by remza on 25.04.2025.
// //
//
// #include "../cpu.h"
// #include <gtest/gtest.h>
//
// TEST(CPU, instruction_ASL_zero_page) {
//   std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
//
//   constexpr std::uint16_t PC = 0xec81;
//   constexpr uint8_t SP = 0x56;
//   constexpr uint8_t A = 0xaa;
//   constexpr uint8_t X = 0xdd;
//   constexpr uint8_t Y = 0xba;
//   constexpr uint8_t P = 0x29;
//
//   memory[0xec81] = 0x06;
//   memory[0xec82] = 0x89;
//   memory[0xec83] = 0x7c;
//   memory[0x0089] = 0x42;
//
//   CPU::CPU cpu{memory, PC, SP, A, X, Y, P};
//
//   cpu.run();
//
//   EXPECT_EQ(cpu.get_PC(), 0xec83);
//   EXPECT_EQ(cpu.get_SP(), 0x56);
//   EXPECT_EQ(cpu.get_A(), 0xaa);
//   EXPECT_EQ(cpu.get_X(), 0xdd);
//   EXPECT_EQ(cpu.get_Y(), 0xba);
//   EXPECT_EQ(cpu.get_P(), 0xa8);
//
//   EXPECT_EQ(memory[0x0089], 0x84);
//   EXPECT_EQ(memory[0xec81], 0x06);
//   EXPECT_EQ(memory[0xec82], 0x89);
//   EXPECT_EQ(memory[0xec83], 0x7c);
// }
//
// TEST(CPU, instruction_ASL_accumulator) {
//   std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
//
//   constexpr std::uint16_t PC = 0xd91a;
//   constexpr uint8_t SP = 0x8e;
//   constexpr uint8_t A = 0x39;
//   constexpr uint8_t X = 0x3e;
//   constexpr uint8_t Y = 0x5d;
//   constexpr uint8_t P = 0xab;
//
//   memory[0xd91a] = 0x0a;
//   memory[0xd91b] = 0x78;
//   memory[0xd91c] = 0x2d;
//
//   CPU::CPU cpu{memory, PC, SP, A, X, Y, P};
//
//   cpu.run();
//
//   EXPECT_EQ(cpu.get_PC(), 0xd91b);
//   EXPECT_EQ(cpu.get_SP(), 0x8e);
//   EXPECT_EQ(cpu.get_A(), 0x72);
//   EXPECT_EQ(cpu.get_X(), 0x3e);
//   EXPECT_EQ(cpu.get_Y(), 0x5d);
//   EXPECT_EQ(cpu.get_P(), 0x28);
//
//   EXPECT_EQ(memory[0xd91a], 0x0a);
//   EXPECT_EQ(memory[0xd91b], 0x78);
//   EXPECT_EQ(memory[0xd91c], 0x2d);
// }
//
// TEST(CPU, instruction_ASL_absolute) {
//   std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
//
//   constexpr std::uint16_t PC = 0xabba;
//   constexpr uint8_t SP = 0x45;
//   constexpr uint8_t A = 0xd9;
//   constexpr uint8_t X = 0xf4;
//   constexpr uint8_t Y = 0x1c;
//   constexpr uint8_t P = 0x68;
//
//   memory[0xabba] = 0x0e;
//   memory[0xabbb] = 0x16;
//   memory[0xabbc] = 0xe0;
//   memory[0xe016] = 0x0a;
//   memory[0xabbd] = 0x8d;
//
//   CPU::CPU cpu{memory, PC, SP, A, X, Y, P};
//
//   cpu.run();
//
//   EXPECT_EQ(cpu.get_PC(), 0xabbd);
//   EXPECT_EQ(cpu.get_SP(), 0x45);
//   EXPECT_EQ(cpu.get_A(), 0xd9);
//   EXPECT_EQ(cpu.get_X(), 0xf4);
//   EXPECT_EQ(cpu.get_Y(), 0x1c);
//   EXPECT_EQ(cpu.get_P(), 0x68);
//
//   EXPECT_EQ(memory[0xabba], 0x0e);
//   EXPECT_EQ(memory[0xabbb], 0x16);
//   EXPECT_EQ(memory[0xabbc], 0xe0);
//   EXPECT_EQ(memory[0xabbd], 0x8d);
//   EXPECT_EQ(memory[0xe016], 0x14);
// }
//
// TEST(CPU, instruction_ASL_zero_page_x) {
//   std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{};
//
//   constexpr std::uint16_t PC = 0xe4fd;
//   constexpr uint8_t SP = 0x66;
//   constexpr uint8_t A = 0xac;
//   constexpr uint8_t X = 0xae;
//   constexpr uint8_t Y = 0x5f;
//   constexpr uint8_t P = 0x6f;
//
//   memory[0xe4fd] = 0x16;
//   memory[0xe4fe] = 0x26;
//   memory[0xe4ff] = 0x59;
//   memory[0x0026] = 0x12;
//   memory[0x00d4] = 0xd2;
//
//   CPU::CPU cpu{memory, PC, SP, A, X, Y, P};
//
//   cpu.run();
//
//   EXPECT_EQ(cpu.get_PC(), 0xe4ff);
//   EXPECT_EQ(cpu.get_SP(), 0x66);
//   EXPECT_EQ(cpu.get_A(), 0xac);
//   EXPECT_EQ(cpu.get_X(), 0xae);
//   EXPECT_EQ(cpu.get_Y(), 0x5f);
//   EXPECT_EQ(cpu.get_P(), 0xed);
//
//   EXPECT_EQ(memory[0x0026], 0x12);
//   EXPECT_EQ(memory[0x00d4], 0xa4);
//   EXPECT_EQ(memory[0xe4fd], 0x16);
//   EXPECT_EQ(memory[0xe4fe], 0x26);
//   EXPECT_EQ(memory[0xe4ff], 0x59);
// }