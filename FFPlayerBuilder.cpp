//
// Created by he li on 22/6/19.
//

#include "FFPlayerBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "FFResample.h"
#include "SDLAudioPlay.h"
#include "SDLVideoView.h"


IDemux *FFPlayerBuilder::createDemux() {
    IDemux *demux = new FFDemux();
    return demux;
}


IDecode *FFPlayerBuilder::createDecode() {
    IDecode *decode = new FFDecode();
    return decode;
}

IResample *FFPlayerBuilder::createResample() {
    IResample *resample = new FFResample();
    return resample;
}

IAudioPlay *FFPlayerBuilder::createAudioPlay() {
    IAudioPlay *audioPlay = new SDLAudioPlay();
    return audioPlay;
}

IVideoView *FFPlayerBuilder::createVideoView() {
    IVideoView *videoView = new SDLVideoView();
    return videoView;
}

IPlayer *FFPlayerBuilder::createPlayer(unsigned char index) {
    return IPlayer::get(index);
}