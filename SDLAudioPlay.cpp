//
// Created by he li on 19/6/19.
//

#include "XParameter.h"
#include "SDLAudioPlay.h"
#include "XLog.h"

extern "C" {
#include <SDL2/SDL.h>
}

static SDL_AudioDeviceID deviceID = 0;

bool SDLAudioPlay::startPlay(XParameter out) {
    // 1. 初始化sdl video 和 audio 组件
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        XLog("SDL_Init with error", SDL_GetError());
        return false;
    }
    SDL_AudioSpec desired_spec;
    desired_spec.freq = out.sample_rate;
    desired_spec.format = AUDIO_S16LSB;
    desired_spec.channels = (Uint8)out.channels;
    desired_spec.silence = 0;
    desired_spec.samples = 1024;
    desired_spec.callback = NULL;
    if ((deviceID = SDL_OpenAudioDevice(NULL, 0, &desired_spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE)) < 2) {
        XLog("SDL_OpenAudioDevice with error deviceID", SDL_GetError());
        return -1;
    }
    SDL_PauseAudioDevice(deviceID, 0);
    XLog("startPlay", "success");
}