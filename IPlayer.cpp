//
// Created by da li on 21/6/19.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "XLog.h"

IPlayer *IPlayer::get(unsigned char index) {
    static IPlayer player[256];
    return &player[index]; // 在多路播放的场景下，有多个IPlayer对象，用索引维护已有的IPlayer。
}

bool IPlayer::open(const char *path) {
    if (!demux || !demux->open(path)) { // 打开解封装
        XLog("demux open", "failed");
        return false;
    }
    // 解码，有可能不许需要，有的视频数据可能未经过编码
    if (!videoDecode || !videoDecode->open(demux->getVParameter()), false) {
        XLog("videoDecode open", "failed");
    }
    // 解码，有可能不许需要，有的音频数据可能未经过编码
    if (!audioDecode || !audioDecode->open(demux->getAParameter())) {
        XLog("audioDecode open", "failed");
    }

    if (outParam.sample_rate <= 0) {
        outParam = demux->getAParameter();
    }
    // 解码，有可能不许需要，有的音频数据可能未经过编码
    if (!resample || !resample->open(demux->getAParameter(), outParam)) {
        XLog("resample open", "failed");
    }
    return true;
}

bool IPlayer::start() {
    if (!demux || !demux->start()) {
        XLog("demux start", "failed");
    }
    if (audioDecode) { // 这里有个解码器启动时序的问题，因为音频比较敏感，所以让音频先解码缓冲
        audioDecode->start();
    }
    if (audioPlay) {
        audioPlay->startPlay(outParam);
    }
    if (videoDecode) {
        videoDecode->start();
    }
    return true;
}