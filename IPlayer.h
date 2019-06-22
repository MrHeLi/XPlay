//
// Created by da li on 21/6/19.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H


#include "XThread.h"

class IDemux;

class IDecode;

class IResample;

class IVideoView;

class IAudioPlay;

class IPlayer : public XThread { // 线程用来做同步
public:
    static IPlayer *get(unsigned char index = 0); // 不是很明白为什么参数是char

    virtual bool open(const char *path);

    virtual bool start();

    bool isHardDecode = false; // 用户设定是否使用硬解码，当前硬解尚未实现 

    IDemux *demux = 0;
    IDecode *videoDecode = 0;
    IDecode *audioDecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:
    IPlayer() {}
};


#endif //XPLAY_IPLAYER_H