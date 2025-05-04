#include "src/apu/apu.h"
#include "src/nes/nes.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

constexpr double GAIN = 5000; // max value for signed 16-bit integer

int main(int argv, char **args) {
  SDL_Init(SDL_INIT_EVERYTHING);

  std::array<std::uint8_t, 0xFFFF> memory;
  NES::NES nes;
  nes.load_rom(memory);

  nes.run();

  return 0;
}
