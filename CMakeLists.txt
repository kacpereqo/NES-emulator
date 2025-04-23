cmake_minimum_required(VERSION 3.29)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wnull-dereference -Wdouble-promotion -Wformat=2")

FetchContent_MakeAvailable(googletest)

# Main executable
add_executable(NES_Emulator
        main.cpp
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
        src/ppu/ppu.h
        src/apu/apu.h
        src/cpu/cpu.cpp
        src/cpu/tests/instruction_arithmetic.cpp
)

# ========== TEST SETUP ==========
enable_testing()

# Add test executable
add_executable(NES_Tests
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
        src/ppu/ppu.h
        src/apu/apu.h
        src/cpu/cpu.cpp
        src/cpu/tests/instruction_arithmetic.cpp
)

# Link test executable with gtest
target_link_libraries(NES_Tests
        gtest
        gtest_main
)


# Discover tests with CTest
include(GoogleTest)
gtest_discover_tests(NES_Tests)
