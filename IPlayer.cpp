//
// Created by da li on 21/6/19.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "XLog.h"

IPlayer *IPlayer::get(unsigned char index) {
    static IPlayer player[256];
    return &player[index]; // 在多路播放的场景下，有多个IPlayer对象，用索引维护已有的IPlayer。
}

void IPlayer::main() {
    while (!isExit) {
        playerMutex.lock();
        if (!videoDecode || !audioPlay) {
            playerMutex.unlock();
            xSleep(2);
            continue;
        }
        // 同步 获取音频的pts 告诉视频
        int apts = audioPlay->pts;
        videoDecode->syncPts = apts;
        playerMutex.unlock();
        xSleep(2);
    }
}

void IPlayer::close() {
    playerMutex.lock();
    // 先关闭主体线程，再清理观察者
    // 同步线程
    XThread::stop();
    // 解封装线程清理
    if (demux) {
        demux->stop();
    }
    // 解码线程
    if (audioDecode) {
        audioDecode->stop();
    }
    if (videoDecode) {
        videoDecode->stop();
    }
    // 音频线程

    // 清理缓冲队列
    if (audioDecode) {
        audioDecode->clear();
    }
    if (videoDecode) {
        videoDecode->clear();
    }
    if (audioPlay) {
        audioPlay->clear();
    }
    // 清理资源
    if (audioPlay) {
        audioPlay->close();
    }
    if (videoView) {
        videoView->close();
    }
    if (audioDecode) {
        audioDecode->close();
    }
    if (videoDecode) {
        videoDecode->close();
    }
    if (demux) {
        demux->close();
    }
    playerMutex.unlock();
}

bool IPlayer::open(const char *path) {
    close();
    playerMutex.lock();
    if (!demux || !demux->open(path)) { // 打开解封装
        XLog("demux open", "failed");
        playerMutex.unlock();
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
    playerMutex.unlock();
    return true;
}

bool IPlayer::start() {
    playerMutex.lock();

    if (videoDecode) {
        videoDecode->start();
    }
    if (audioPlay) {
        audioPlay->startPlay(outParam);
    }
    if (audioDecode) { // 这里有个解码器启动时序的问题，因为音频比较敏感，所以让音频先解码缓冲
        audioDecode->start();
    }
    if (!demux || !demux->start()) {
        XLog("demux start", "failed");
        playerMutex.unlock();
        return false;
    }
    XThread::start();

    playerMutex.unlock();
    return true;
}