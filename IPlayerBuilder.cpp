//
// Created by da li on 22/6/19.
//

#include "IPlayerBuilder.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IVideoView.h"
#include "IAudioPlay.h"

IPlayer *IPlayerBuilder::buildPlayer(unsigned char index) {
    IPlayer *player = createPlayer(index);
    // 创建解封装器
    IDemux *demux = createDemux();

    // 1. 创建视频播放界面 2. 创建视频解码器 3. 将视频界面作为视频解码器的观察者
    IVideoView *videoView = createVideoView();
    IDecode *vDecode = createDecode();
    vDecode->addObserver(videoView);
    // 1. 创建音频解码器 2. 创建重采样模块 3. 将重采样模块作为音频解码器的观察者
    IDecode *aDecode = createDecode();
    IResample *resample = createResample();
    aDecode->addObserver(resample);
    // 1. 创建音频播放器 2. 将音频播放器作为重采样模块的观察者
    IAudioPlay *audioPlay = createAudioPlay();
    resample->addObserver(audioPlay);
    // 将音视频解码器作为解封装的观察者
    demux->addObserver(vDecode);
    demux->addObserver(aDecode);

    player->demux = demux;
    player->videoDecode = vDecode;
    player->audioDecode = aDecode;
    player->videoView = videoView;
    player->resample = resample;
    player->audioPlay = audioPlay;
    return player;
}