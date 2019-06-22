//
// Created by da li on 21/6/19.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
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
    XLog("demux open", "success");
    // 解码，有可能不许需要，有的视频数据可能未经过编码
    if (!videoDecode || !videoDecode->open(demux->getVParameter()), false) {
        XLog("videoDecode open", "failed");
    }
    XLog("videoDecode open", "success");
    // 解码，有可能不许需要，有的音频数据可能未经过编码
    if (!audioDecode || !audioDecode->open(demux->getAParameter())) {
        XLog("audioDecode open", "failed");
    }
    XLog("audioDecode open", "success");

    XParameter outParam = demux->getAParameter();
    // 解码，有可能不许需要，有的音频数据可能未经过编码
    if (!resample || !resample->open(demux->getAParameter(), outParam)) {
        XLog("resample open", "failed");
    }
    XLog("resample open", "success");
    return true;
}

bool IPlayer::start() {
    return true;
}