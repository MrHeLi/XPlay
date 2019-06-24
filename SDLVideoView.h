//
// Created by he li on 16/6/19.
//

#ifndef XPLAY_SDLVIDEOVIEW_H
#define XPLAY_SDLVIDEOVIEW_H

#include "IVideoView.h"

class SDLVideoView : public IVideoView {
public:
    // 该接口用于传递系统窗口，以便渲染控件可以绑定该窗口，交给具体的渲染控件实现。
    // 主要用在在Android系统中。非安卓系统window参数可为NULL，
    virtual void setRender(void *window, TextureType textureType);

    virtual void close();

    // 渲染控件核心渲染接口，子类实现
    virtual void render(XData data);

    void *mWindow = 0;

    void *mRenderer = 0;

    void *mTexture = 0;

    int mWidth = 1080; // 默认宽

    int mHeight = 720; // 默认高

    TextureType type = Texture_YUV420P;

private:
    void initSDL(int width, int height);

    std::mutex videoMutex;
};


#endif //XPLAY_SDLVIDEOVIEW_H
