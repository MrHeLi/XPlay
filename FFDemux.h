//
// Created by he li on 12/6/19.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


#include "IDemux.h"
struct AVFormatContext;

class FFDemux : public IDemux {
public:
    FFDemux();
    // 打开文件，或者流媒体rtsp、http、rmtp
    virtual bool open(const char *url);

    // 获取视频流的参数
    virtual XParameter getVParameter();

    // 获取音频流的参数
    virtual XParameter getAParameter();

    // 读取一帧数据，内存由调用者释放
    virtual XData read();

private:
    AVFormatContext *ic = 0;
    int audioStreamId = 1;
    int videoStreamId = 0;
};


#endif //XPLAY_FFDEMUX_H
