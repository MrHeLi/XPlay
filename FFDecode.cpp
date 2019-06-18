//
// Created by he li on 16/6/19.
//

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "FFDecode.h"
#include "XLog.h"

bool FFDecode::open(XParameter xParameter) {
    if (!xParameter.codecParameters) {
        return false;
    }
    AVCodecParameters *avCodecParameters = xParameter.codecParameters;
    // 1. 查找解码器
    AVCodec *codec = avcodec_find_decoder(avCodecParameters->codec_id);
    if (!codec) {
        XLog("FFDecode::open", "avcodec_find_decoder failde");
        return false;
    }
    XLog("FFDecode::open", "success");
    // 2. 创建解码器上下文，并复制参数
    avCodecContext = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(avCodecContext, avCodecParameters);
    avCodecContext->thread_count = 8;

    // 3. 打开解码器
    int result = avcodec_open2(avCodecContext, codec, 0);
    if (result != 0) {
        XLog("FFDecode::open:avcodec_open2 failed:", av_err2str(result));
        return false;
    }
    XLog("FFDecode::open:avcodec_open2 ", "success");
    if (avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO) {
        this->isAudio = false;
    } else {
        this->isAudio = true;
    }
    return true;
}

bool FFDecode::sendPacket(XData pkt) {
    if (pkt.size <= 0 || !pkt.data) {
        return false;
    }
    if (!avCodecContext) {
        return false;
    }

    int result = avcodec_send_packet(avCodecContext, (AVPacket *) (pkt.data));
    if (result != 0) {
        return false;
    }
    return true;
}

// 从线程中获取解码数据的接口
XData FFDecode::receiveFrame() {
    if (!avCodecContext) {
        return XData();
    }

    if (frame == 0) {
        frame = av_frame_alloc();
    }
    int result = avcodec_receive_frame(avCodecContext, frame);
    if (result != 0) {
        return XData();
    }
    XData data;
    data.data = (unsigned char *) frame;
    data.width = frame->width;
    data.height = frame->height;
    if (avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO) {
        data.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
    } else if (avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO) {
        // 样本字节数 * 单通道样本数 * 通道数
        data.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * frame->channels;
    } else {
        data.size = 0; // 其它数据暂不处理，先设置一个0
    }
    return data;
}