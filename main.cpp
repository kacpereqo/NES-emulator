#include "src/apu/apu.h"
#include "src/cpu/cpu.h"
#include "src/ppu/ppu.hpp"

#include <SDL3/SDL.h>

#include <utility>

class NES {
  CPU::CPU cpu;
  Bus::Bus bus;
  PPU::PPU ppu;

  explicit NES(std::vector<std::uint8_t> data) : cpu(bus), ppu(bus, cpu)
  {
	bus.insert_cartridge(std::move(data));
  	bus.connect_ppu(ppu);
  }

	void run()
  {
	cpu.run();
  	ppu.run();
  	ppu.run();
  	ppu.run();
  }
};

int main(int argc, char* argv[]) {
 //  SDL_Init(SDL_INIT_VIDEO);
 //
	// std::uint32_t WIDTH = 256;
	// std::uint32_t HEIGHT = 240;
 //
 //  SDL_Window *window = SDL_CreateWindow(
 //      "SDL3 Window",
 //      WIDTH, HEIGHT,
 //      SDL_WINDOW_RESIZABLE
 //  );
 //
 //  SDL_Delay(3000);
 //
 //  SDL_DestroyWindow(window);
 //  SDL_Quit();
}