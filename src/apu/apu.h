//
// Created by thinkPaździerż on 19.04.2025.
//

#ifndef APU_H
#define APU_H

#include <SDL2/SDL.h>
#include <array>
#include <cmath>
#include <cstdint>

// Registers 	Channel 	Units
// $4000–$4003 	Pulse 1 	Timer, length counter, envelope, sweep
// $4004–$4007 	Pulse 2 	Timer, length counter, envelope, sweep
// $4008–$400B 	Triangle 	Timer, length counter, linear counter
// $400C–$400F 	Noise 	    Timer, length counter, envelope, linear feedback
// shift register $4010–$4013 	DMC 	    Timer, memory reader, sample buffer,
// output unit $4015 	    All 	    Channel enable and length counter
// status $4017 	    All 	    Frame counter

namespace APU {
constexpr std::uint8_t CHANNEL_COUNT{5};

namespace Status {
enum Status : std::uint8_t {
  Pulse1 = 1 << 0,
  Pulse2 = 1 << 1,
  Triangle = 1 << 2,
  Noise = 1 << 3,
  DMC = 1 << 4,
};

}

namespace FrameCounter {
enum FrameCounter : std::uint8_t {
  IRQ = 1 << 6,
  Mode = 1 << 7,
};
}

class APU {
public:
  explicit APU(std::array<std::uint8_t, 0xFFFF> &memory) : memory{memory} {
    this->init();
  }
  ~APU() { SDL_CloseAudioDevice(this->audio_device); }

  void init() {
    audio_spec.freq = 44100;          // sampling rate
    audio_spec.format = AUDIO_S16SYS; // sample format
    audio_spec.channels = 1;          // number of channels
    audio_spec.samples = 4096;        // buffer size
    audio_spec.callback = nullptr;

    this->audio_device =
        SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, 0);
  }

  void run() {
    // mix

    double x = 0;
    for (int i = 0; i < audio_spec.freq * 3; i++) {
      x += .05f;

      // SDL_QueueAudio expects a signed 16-bit integer
      auto sample = static_cast<std::int16_t>(sin(x) * 5000);

      int sample_size = sizeof(Sint16) * 1;
      SDL_QueueAudio(audio_device, &sample, sample_size);
    }

    SDL_PauseAudioDevice(audio_device, 0);
    SDL_Delay(1000 * 3); // wait for 3 seconds
    SDL_CloseAudioDevice(audio_device);

    // const std::uint8_t pulse1 = generate_pulse_1();
    // const std::uint8_t pulse2 = generate_pulse_2();
    // const std::uint8_t triangle = generate_triangle();
    // const std::uint8_t noise = generate_noise();
    // const std::uint8_t dmc = generate_dmc();
    //
    // const std::uint8_t pulse_out = 95.88 / (8128 / (pulse1 + pulse2) + 100);
    // const std::uint8_t tnd_out = 159.79 / (1 / ( triangle / 8227 + noise /
    // 12241 + dmc / 22638) + 100);
    //
    // const std::uint8_t output = pulse_out + tnd_out;
  }

private:
  SDL_AudioDeviceID audio_device;
  SDL_AudioSpec audio_spec{0};

  std::uint8_t generate_pulse_1();
  std::uint8_t generate_pulse_2();
  std::uint8_t generate_triangle();
  std::uint8_t generate_noise();
  std::uint8_t generate_dmc();

  std::array<std::uint8_t, CHANNEL_COUNT> channels;
  std::array<std::uint8_t, 0xFFFF> &memory;
};
} // namespace APU

#endif // APU_H
