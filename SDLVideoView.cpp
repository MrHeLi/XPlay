//
// Created by he li on 16/6/19.
//

#include <libavutil/frame.h>
#include "SDL2/SDL.h"
#include "SDLVideoView.h"
#include "XLog.h"

// 该接口用于传递系统窗口，以便渲染控件可以绑定该窗口，交给具体的渲染控件实现。
// 主要用在在Android系统中。非安卓系统window参数可为NULL，该接口也可以做一些初始化操作
void SDLVideoView::setRender(void *window) {
//    this->mWidth = width;
//    this->mHeight = height;
//    initSDL();
}

// 渲染控件核心渲染接口，子类实现
void SDLVideoView::render(XData data) {
    if (mWindow == 0) {
        initSDL(data.width, data.height); // TODO:完善的时候要考虑宽高的变化
    }
    if (mTexture == 0) {
        return;
    }

    AVFrame *avFrame = (AVFrame *) data.data;
    // 像素格式刚好是YUV420P的，不用做像素格式转换
    cout << "avFrame pts : " << avFrame->pts << " color format:" << avFrame->format << endl;
    int result = SDL_UpdateYUVTexture((SDL_Texture *)mTexture, NULL, avFrame->data[0], avFrame->linesize[0],
                                  avFrame->data[1], avFrame->linesize[1], avFrame->data[2],
                                  avFrame->linesize[2]);
    SDL_RenderClear((SDL_Renderer *)mRenderer);
    SDL_RenderCopy((SDL_Renderer *)mRenderer, (SDL_Texture *)mTexture, NULL, NULL);
    SDL_RenderPresent((SDL_Renderer *)mRenderer);
}

void SDLVideoView::initSDL(int width, int height) {
    this->mWidth = width;
    this->mHeight = height;
    // 1. 初始化sdl video 和 audio 组件
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        XLog("SDL_Init", "failed");
        return;
    }
    // 2. 创建窗体
    this->mWindow = SDL_CreateWindow("XPlayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                     mWidth, mHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    if (this->mWindow == NULL) {
        XLog("SDL_CreateWindow", "failed");
        return;
    }
    XLog("SDL_CreateWindow", "success");
    //3. 根据窗体创建渲染器
    this->mRenderer = SDL_CreateRenderer((SDL_Window *) this->mWindow, -1, 0);
    //4. 创建纹理
    this->mTexture = SDL_CreateTexture((SDL_Renderer *) this->mRenderer, SDL_PIXELFORMAT_IYUV,
                                       SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
}