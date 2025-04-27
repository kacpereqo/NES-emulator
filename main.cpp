#include <iostream>
#include "src/nes/nes.h"
#include "src/apu/apu.h"
#include <SDL2/SDL.h>

int main(int argv, char** args) {
    std::array<std::uint8_t, 0xFFFF> memory{};
    APU::APU apu{memory};

    // SDL_Init(SDL_INIT_AUDIO);

    // // the representation of our audio device:
    //
    // // setting up our audio format:
    // SDL_AudioSpec audio_spec = {0};
    // audio_spec.freq = 44100; // sampling rate
    // audio_spec.format = AUDIO_S16SYS; // sample format
    // audio_spec.channels = 1; // number of channels
    // audio_spec.samples = 4096; // buffer size
    // audio_spec.callback = nullptr;
    //
    // // opening the default audio device:
    // SDL_AudioDeviceID audio_device = SDL_OpenAudioDevice(nullptr, 0, &audio_spec, nullptr, 0);
    //
    // // pushing 3 seconds of samples to the audio buffer:
    // double x = 0;
    // for (int i = 0; i < audio_spec.freq * 3; i++) {
    //     x += .05f;
    //
    //     // SDL_QueueAudio expects a signed 16-bit integer
    //     Sint16 sample = sin(x) * GAIN;
    //
    //     int sample_size = sizeof(Sint16) * 1;
    //     SDL_QueueAudio(audio_device, &sample, sample_size);
    // }
    //
    // // unpausing the audio device: starts playing the queued data
    // SDL_PauseAudioDevice(audio_device, 0);
    //
    // SDL_Delay(3 * 1000);
    //
    // SDL_CloseAudioDevice(audio_device);

    return 0;
}
