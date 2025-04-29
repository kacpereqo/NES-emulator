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
set(SDL2MIXER_WAVPACK OFF CACHE BOOL "" FORCE)

set(SDL2_LIB_DIR C:/Users/remza/CLionProjects/NES-emulator/external/SDL2/lib)
set(SDL2_INCLUDE_DIR C:/Users/remza/CLionProjects/NES-emulator/external/SDL2/include)
set(SDL2_LIBRARY C:/Users/remza/CLionProjects/NES-emulator/external/SDL2/bin)
set (CMAKE_BUILD_DIR "C:/Users/remza/CLionProjects/NES-emulator/cmake-build-debug")
set(OUTPUT_DIR "${CMAKE_BUILD_DIR}")


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://codeload.github.com/google/googletest/zip/refs/tags/v1.13.0
)

FetchContent_MakeAvailable(googletest)



include_directories(
        ${SDL2_INCLUDE_DIR}
)

link_directories(
        ${SDL2_LIB_DIR}
)


# Main executable
add_executable(NES_Emulator
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
        main.cpp
)

# ========== TEST SETUP ==========
enable_testing()

# Add test executable
add_executable(NES_Tests
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

target_link_libraries(NES_Emulator PRIVATE
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
)

message(STATUS "Copying all dependencies to destination folder...")
file(GLOB PROJECT_DEPENDENCIES ${SDL2_LIBRARY}/*.dll)

foreach(DEPENDENCY ${PROJECT_DEPENDENCIES})
    get_filename_component(DEPENDENCY_NAME ${DEPENDENCY} NAME)
    message(STATUS "Copying ${DEPENDENCY_NAME} to ${OUTPUT_DIR}")
    file(COPY ${DEPENDENCY} DESTINATION ${OUTPUT_DIR})
endforeach ()

include(GoogleTest)
gtest_discover_tests(NES_Tests)