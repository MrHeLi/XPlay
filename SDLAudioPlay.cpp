//
// Created by he li on 19/6/19.
//

#include <thread>
#include "XParameter.h"
#include "SDLAudioPlay.h"
#include "XLog.h"

extern "C" {
#include <SDL2/SDL.h>
}

static SDL_AudioDeviceID deviceID = 0;


//void SDLAudioPlay::fill_audio(void *udata, Uint8 *stream, int len) {
//    //SDL 2.0
//    SDL_memset(stream, 0, len);
////    if (audio_len == 0)
////        return;
////    len = (len > audio_len ? audio_len : len);
//    XData data = getData();
////    len = len >
//    SDL_MixAudio(stream, data.data, data.size, SDL_MIX_MAXVOLUME);
//    data.clear();
////    audio_pos += len;
////    audio_len -= len;
//}

bool SDLAudioPlay::startPlay(XParameter out) {
    // 1. 初始化sdl video 和 audio 组件
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        XLog("SDL_Init with error", SDL_GetError());
        return false;
    }
    SDL_AudioSpec desired_spec;
    desired_spec.freq = out.sample_rate;
    desired_spec.format = AUDIO_S16LSB;
    desired_spec.channels = (Uint8) out.channels;
    desired_spec.silence = 0;
    desired_spec.samples = 1024;
    desired_spec.callback = NULL;
    if ((deviceID = SDL_OpenAudioDevice(NULL, 0, &desired_spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE)) < 2) {
        XLog("SDL_OpenAudioDevice with error deviceID", SDL_GetError());
        return false;
    }
    SDL_PauseAudioDevice(deviceID, 0);

    if (SDL_OpenAudio(&desired_spec, NULL) < 0) {
        XLog("SDL_OpenAudioDevice with error", SDL_GetError());
        return false;
    }
    SDL_PauseAudio(0);
    XLog("startPlay", "success");

    // 开一个线程，专门往音频设备写数据
    thread th1(&SDLAudioPlay::run, this);
    th1.detach();
}

void SDLAudioPlay::run() {
    XLog("SDLAudioPlay", "run_begin");
    while (!isExit) {
        XData data = getData(); // 如果音频队列中没有数据，阻塞
        if (data.size <= 0) {
            XLog("getData()", "size < 0");
        }
        SDL_QueueAudio(deviceID, data.data, data.size);
    }
    XLog("SDLAudioPlay", "run_end");
}