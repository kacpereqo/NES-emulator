import orjson

from opcode_table import opcode_table


def reduce_json_file(opcode, n):
    file_path = f"data/{opcode}.json"

    with open(file_path, "r", encoding="utf-8") as f:
        data = f.read()

        data = orjson.loads(data)
        data = data[:n]

    with open(file_path, "w", encoding="utf-8") as f:
        f.write(orjson.dumps(data).decode("utf-8"))


def generate_test(opcode, n=0):
    file_path = f"data/{opcode :>02x}.json"

    with open(file_path, "r") as f:
        data = f.read()
        json = orjson.loads(data)
        json = json[n]

        initial_state = json["initial"]
        final_state = json["final"]

        memory_initial_state = "\n\t".join(
            f"memory[0x{address :>04x}] = 0x{value :>02x};" for address, value in initial_state['ram'])
        memory_final_state = "\n\t".join(
            [f"EXPECT_EQ(bus.cpu_read(0x{address :>04x}), 0x{value :>02x});" for address, value in final_state['ram']])

        if "???" in opcode_table[opcode] or "NOP" in opcode_table[opcode]:
            return ""

        # GTEST_SKIP() << "Skipping test for opcode 0x{opcode :>02x}";

        result = f"""
        TEST(CPU, instruction_{opcode_table[opcode]}) {{
        std::array<std::uint8_t, CPU::MEMORY_SIZE> memory{{}};
        


        constexpr std::uint16_t PC = 0x{(initial_state['pc']):>04x};
        constexpr uint8_t SP       = 0x{(initial_state['s']) :>02x};
        constexpr uint8_t A        = 0x{(initial_state['a']) :>02x};
        constexpr uint8_t X        = 0x{(initial_state['x']) :>02x};
        constexpr uint8_t Y        = 0x{(initial_state['y']) :>02x};
        constexpr uint8_t P        = 0x{(initial_state['p']) :>02x};

        {memory_initial_state}
        
        Bus::Bus bus{{memory}};

        CPU::CPU cpu{{bus, PC, SP, A, X, Y, P}};

        cpu.run();

        EXPECT_EQ(cpu.get_PC(), 0x{final_state['pc'] :>04x});
        EXPECT_EQ(cpu.get_SP(), 0x{final_state['s'] :>02x});
        EXPECT_EQ(cpu.get_A(),  0x{final_state['a'] :>02x});
        EXPECT_EQ(cpu.get_X(),  0x{final_state['x'] :>02x});
        EXPECT_EQ(cpu.get_Y(),  0x{final_state['y'] :>02x});
        EXPECT_EQ(cpu.get_P(),  0x{final_state['p'] :>02x});

        {memory_final_state}
        }}"""

        return result


if __name__ == "__main__":
    code = ""

    for opcode in range(0x00, 0xFF + 1):
        if opcode in opcode_table:
            if "???" in opcode_table[opcode] or "NOP" in opcode_table[opcode]:
                continue
            code += generate_test(opcode, 0)

    print(code)
