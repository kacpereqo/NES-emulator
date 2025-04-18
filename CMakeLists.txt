cmake_minimum_required(VERSION 3.29)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(NES_Emulator main.cpp
        cpu/cpu.cpp
        cpu/cpu.h)
