cmake_minimum_required(VERSION 3.29)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 23)

SET(PROJECT_NAME NES_Emulator)

SET (GTEST_VERSION 1.14.0)
SET (SDL2_VERSION 2.30.2)
SET (SDL2_MIXER_VERSION 2.8.1)

set(SDL2MIXER_OPUS  OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_FLAC   OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MOD OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MOD_XMP OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MOD_MODPLUG OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MIDI_FLUIDSYNTH OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MP3_MPG123 OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MP3_SMPEG OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_VORBIS_VORBISFILE OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_VORBIS_TREMOR OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_FLAC_DRFLAC OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_FLAC_LIBFLAC OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_MIDI_FLUIDSYNTH OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-${SDL2_VERSION}
)

FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-${SDL2_MIXER_VERSION}
)


FetchContent_MakeAvailable(SDL2_mixer)


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

target_link_libraries(NES_Emulator PRIVATE SDL2main SDL2 SDL2_mixer)


# Discover tests with CTest
include(GoogleTest)
gtest_discover_tests(NES_Tests)