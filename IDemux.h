//
// Created by he li on 12/6/19.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

// 解封装接口
class IDemux : public IObserver {
public:
    // 打开文件，或者流媒体rtsp、http、rmtp
    virtual bool open(const char *url) = 0;

    virtual void close() = 0;

    // 获取视频流的参数
    virtual XParameter getVParameter() = 0;

    // 获取音频流的参数
    virtual XParameter getAParameter() = 0;

    // 读取一帧数据，内存由调用者释放
    virtual XData read() = 0;

    int totalMs;

protected:
    virtual void main();
};


#endif //XPLAY_IDEMUX_H
