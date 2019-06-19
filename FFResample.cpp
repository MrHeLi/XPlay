//
// Created by he li on 19/6/19.
//

#include "FFResample.h"
#include "XLog.h"


extern "C" {
#include "libswresample/swresample.h"
#include <libavcodec/avcodec.h>
}

bool FFResample::open(XParameter in, XParameter out) {
    //音频重采样上下文初始化
    aCtx = swr_alloc();
    aCtx = swr_alloc_set_opts(aCtx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16, in.codecParameters->sample_rate,
                              av_get_default_channel_layout(in.codecParameters->channels),
                              (AVSampleFormat) in.codecParameters->format, in.codecParameters->sample_rate,
                              0, 0);
    int result = swr_init(aCtx);
    if (result != 0) {
        XLog("FFResample", "swr_init failed!");
    }
    XLog("FFResample", "swr_init success!");
    outChannels = in.codecParameters->channels;
    outFormat = AV_SAMPLE_FMT_S16;
}

XData FFResample::resample(XData inData) {
    if (inData.size <= 0 || !inData.data || !aCtx) {
        return XData();
    }
    AVFrame *frame = (AVFrame *)inData.data;
    // 输出控件的分配
    XData outData;
    // 数据的大小 = 通道数 * 单通道样本数 * 样本字节大小
    int outSize = outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)outFormat);
    if (outSize <= 0) {
        return XData();
    }
    outData.alloc(outSize);
    uint8_t *outArray[2] = {0};
    outArray[0] = outData.data;
    int len = swr_convert(aCtx, outArray, frame->nb_samples, (const uint8_t **)frame->data, frame->nb_samples);
    if (len <= 0) {
        outData.clear();
        return XData();
    }
    XLog("FFResample len ", len);
    return XData();
}