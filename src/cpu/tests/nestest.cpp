//
// Created by debilian on 24.03.2026.
//

// https://www.qmtpro.com/~nes/misc/nestest.txt

#include "../cpu.h"
#include <gtest/gtest.h>
#include <fstream>

#include "../../bus/fake_bus.hpp"

TEST(CPU, nestest_full_validation) {
	std::ifstream rom_file("assets/nestest.nes", std::ios::binary);
	ASSERT_TRUE(rom_file.is_open());

	std::vector<uint8_t> rom(
		(std::istreambuf_iterator(rom_file)),
		std::istreambuf_iterator<char>()
	);

	constexpr uint16_t PC = 0xC000;
	constexpr uint8_t A = (0x00);
	constexpr uint8_t X = (0x00);
	constexpr uint8_t Y = (0x00);
	constexpr uint8_t P = (0x24);
	constexpr uint8_t SP = (0xFD);

    Bus::FakeBus bus{rom};
	CPU::CPU cpu{bus, PC, SP, A, X, Y, P};

	std::ifstream log("assets/nestest.log");
	ASSERT_TRUE(log.is_open());

	std::string line;

	for (int i = 0; i < 5000 && std::getline(log, line); ++i) {
		uint16_t expected_PC;
		uint8_t expected_A, expected_X, expected_Y, expected_P, expected_SP;

		sscanf(line.c_str(),
			   "%04hx %*[^A]A:%02hhx X:%02hhx Y:%02hhx P:%02hhx SP:%02hhx",
			   &expected_PC,
			   &expected_A,
			   &expected_X,
			   &expected_Y,
			   &expected_P,
			   &expected_SP);

		ASSERT_EQ(cpu.get_PC(), expected_PC) << "Step " << i;
		ASSERT_EQ(cpu.get_A(), expected_A) << "Step " << i;
		ASSERT_EQ(cpu.get_X(), expected_X) << "Step " << i;
		ASSERT_EQ(cpu.get_Y(), expected_Y) << "Step " << i;
		ASSERT_EQ(cpu.get_P(), expected_P) << "Step " << i;
		ASSERT_EQ(cpu.get_SP(), expected_SP) << "Step " << i;

		cpu.run();
	}
}