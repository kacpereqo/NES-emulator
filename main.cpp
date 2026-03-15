#include "src/apu/apu.h"
#include "src/cpu/cpu.h"
#include "src/ppu/ppu.hpp"

#include <SDL3/SDL.h>

class NES {
  CPU::CPU cpu;
  Bus::Bus bus;
  PPU::PPU ppu;

  NES(std::array<std::uint8_t, 0x10000> data) : cpu(bus), bus(data, ppu), ppu(bus) {}
};

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
      "SDL3 Window",
      800,
      600,
      SDL_WINDOW_RESIZABLE
  );

  SDL_Delay(3000);

  SDL_DestroyWindow(window);
  SDL_Quit();
}