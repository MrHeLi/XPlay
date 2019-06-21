//
// Created by he li on 16/6/19.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H

#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    virtual bool open(XParameter xParameter, bool isHard = false);

    // 发送数据到解码器解码
    virtual bool sendPacket(XData pkt);
    // 从线程中获取解码数据的接口, 再次调用回复用上次空间，线程不安全
    virtual XData receiveFrame();

protected:
    AVCodecContext *avCodecContext = 0;

    // avframe 在ffmpeg内部会重复利用，所以提取一个成员出来
    AVFrame *frame = 0;
};


#endif //XPLAY_FFDECODE_H
