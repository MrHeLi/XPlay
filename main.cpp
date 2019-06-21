#include <iostream>
#include <string>
#include "IDemux.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "IVideoView.h"
#include "SDLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SDLAudioPlay.h"

using namespace std;

class TestObserver : public IObserver {
public:
    void update(XData data) {
//        cout << "TestObserver receive data.size = " << data.size << endl;
    }
};

int main() {
    TestObserver *observer = new TestObserver();
    IDemux *demux = new FFDemux();
//    demux->addObserver(observer);
    string source_url = "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4";
    demux->open(source_url.c_str());

    IVideoView *videoView = new SDLVideoView();

    IDecode *vDecode = new FFDecode();
    vDecode->open(demux->getVParameter(), true);
    vDecode->addObserver(videoView);

    IDecode *aDecode = new FFDecode();
    aDecode->open(demux->getAParameter());

    IResample *resample = new FFResample();
    XParameter outParam = demux->getAParameter();
    resample->open(demux->getAParameter(), outParam);
    aDecode->addObserver(resample);

    IAudioPlay *audioPlay = new SDLAudioPlay();
    audioPlay->startPlay(outParam);
    resample->addObserver(audioPlay);

    demux->addObserver(vDecode);
    demux->addObserver(aDecode);

    demux->start();
    aDecode->start();
    vDecode->start();


    xSleep(300000);
//    while (1) {
//        XData data = demux->read();
//        cout << "data size = " << data.size << endl;
//    }
}