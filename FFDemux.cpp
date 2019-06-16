//
// Created by he li on 12/6/19.
//

#include "FFDemux.h"
#include "XLog.h"

extern "C" {
#include <libavformat/avformat.h>
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        // 注册解封装器
        av_register_all();
        // 注册解码器；
        avcodec_register_all();
        // 注册网络
        avformat_network_init();
    }
}

// 打开文件，或者流媒体rtsp、http、rmtp
bool FFDemux::open(const char *url) {
    XLog("FFDemux::open", url);
    int result = avformat_open_input(&ic, url, nullptr, nullptr);
    if (result != 0) {
        XLog("avformat_open_input", "failed");
    }
    XLog("avformat_open_input", "success");

    result = avformat_find_stream_info(ic, nullptr);
    if (result != 0) {
        XLog("avformat_find_stream_info", "failed");
    }
    this->totalMs = ic->duration/(AV_TIME_BASE/1000);
    XLog("totalms", this->totalMs)
    getVParameter();
    getAParameter();
    return true;
}

// 读取一帧数据，内存由调用者释放
XData FFDemux::read() {
    if (!ic) {
        return XData();
    }
    AVPacket *packet = av_packet_alloc();
    int result = av_read_frame(ic, packet);
    if (result != 0) {
        av_packet_free(&packet);
        return XData();
    }
//    cout << "FFDemux::read:" << "packate size = " << packet->size << " pts:" << packet->pts << endl;
    XData data;
    data.data = (unsigned char *)packet;
    data.size = packet->size;
    if (packet->stream_index == videoStreamId) {
        data.isAudio = false;
    } else if (packet->stream_index == audioStreamId) {
        data.isAudio = true;
    } else {
        av_packet_free(&packet);
        return XData();
    }
    return data;
}

// 获取视频流的参数
XParameter FFDemux::getVParameter() {
    if (!ic) {
        XLog("FFDemux::getVParameter failed", "");
        return XParameter();
    }
    // 获取视频流参数
    int streamId = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (streamId < 0) {
        XLog("FFDemux::getVParameter failed", "");
        return XParameter();
    }
    videoStreamId = streamId;
    XParameter parameter;
    parameter.codecParameters = ic->streams[streamId]->codecpar;
    XLog("FFDemux::getVParameter success", "");
    return parameter;
}

// 获取音频流的参数
XParameter FFDemux::getAParameter() {
    if (!ic) {
        XLog("FFDemux::getVParameter failed", "");
        return XParameter();
    }
    // 获取视频流参数
    int streamId = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (streamId < 0) {
        XLog("FFDemux::getVParameter failed", "");
        return XParameter();
    }
    audioStreamId = streamId;
    XParameter parameter;
    parameter.codecParameters = ic->streams[streamId]->codecpar;
    XLog("FFDemux::getVParameter success", "");
    return parameter;
}