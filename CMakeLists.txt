cmake_minimum_required(VERSION 3.29)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

include(cmake/CPM.cmake)


add_executable(${PROJECT_NAME}
        src/cpu/cpu.h
        src/cpu/instructions/load.cpp
        src/cpu/instructions/transfer.cpp
        src/cpu/instructions/stack.cpp
        src/cpu/instructions/logical.cpp
        src/cpu/instructions/arithmetic.cpp
        src/cpu/instructions/increment.cpp
        src/cpu/instructions/shift.cpp
        src/cpu/instructions/jump.cpp
        src/cpu/instructions/branch.cpp
        src/cpu/instructions/control.cpp
        src/cpu/instructions/system.cpp
        src/cpu/utils.cpp
        src/nes/nes.h
        src/ppu/ppu.hpp
        src/apu/apu.h
        src/cpu/cpu.cpp
        main.cpp
        src/ppu/enums.hpp
        src/bus/bus.hpp
        src/bus/bus.hpp
        src/cpu/enum.hpp
        src/bus/bus.cpp
        src/bus/fake_bus.cpp
        src/bus/fake_bus.hpp
        src/bus/abstract_bus.hpp
        src/ppu/ppu.cpp
)
enable_testing()

add_executable(${PROJECT_NAME}-TESTS
        src/cpu/tests/instruction_shift.cpp
        src/cpu/tests/instruction_arithmetic.cpp
        src/cpu/cpu.h
        src/cpu/instructions/load.cpp
        src/cpu/instructions/transfer.cpp
        src/cpu/instructions/stack.cpp
        src/cpu/instructions/logical.cpp
        src/cpu/instructions/arithmetic.cpp
        src/cpu/instructions/increment.cpp
        src/cpu/instructions/shift.cpp
        src/cpu/instructions/jump.cpp
        src/cpu/instructions/branch.cpp
        src/cpu/instructions/control.cpp
        src/cpu/instructions/system.cpp
        src/cpu/utils.cpp
        src/nes/nes.h
        src/ppu/ppu.hpp
        src/apu/apu.h
        src/cpu/cpu.cpp
        src/cpu/tests/instruction_arithmetic.cpp
)


include(cmake/Fetch-gtest.cmake)
include(cmake/Fetch-SDL3.cmake)