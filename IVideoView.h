//
// Created by he li on 16/6/19.
//

#ifndef XPLAY_IVIDEOVIEW_H
#define XPLAY_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

enum TextureType {
    Texture_YUV420P = 0,
    Texture_NV12 = 25,
    Texure_NV21 = 26
};

class IVideoView : public IObserver {
public:
    // 该接口用于传递系统窗口，以便渲染控件可以绑定该窗口，交给具体的渲染控件实现。
    // 主要用在在Android系统中。非安卓系统window参数可为NULL，type 为yuv格式
    virtual void setRender(void *window, TextureType type) = 0;

    virtual void close() = 0;

    // 渲染控件核心渲染接口，子类实现
    virtual void render(XData data) = 0;

    // 接口提供统一接口
    virtual void update(XData data);
};


#endif //XPLAY_IVIDEOVIEW_H
