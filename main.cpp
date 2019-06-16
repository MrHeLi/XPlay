#include <iostream>
#include <string>
#include "IDemux.h"
#include "FFDemux.h"
#include "FFDecode.h"

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

    IDecode *vDecode = new FFDecode();
    vDecode->open(demux->getVParameter());

    IDecode *aDecode = new FFDecode();
    aDecode->open(demux->getAParameter());

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