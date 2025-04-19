cmake_minimum_required(VERSION 3.29)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(NES_Emulator main.cpp
        cpu/cpu.h
        cpu/instructions/load.cpp
        cpu/instructions/transfer.cpp
        cpu/instructions/stack.cpp
        cpu/instructions/logical.cpp
        cpu/instructions/arithmetic.cpp
        cpu/instructions/increment.cpp
        cpu/instructions/shift.cpp
        cpu/instructions/jump.cpp
        cpu/instructions/branch.cpp
        cpu/instructions/control.cpp
        cpu/instructions/system.cpp
        cpu/utils.cpp
        nes/nes.h
        ppu/ppu.h
        apu/apu.h)
