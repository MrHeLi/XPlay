//
// Created by he li on 12/6/19.
//

#include "IDemux.h"
#include "XLog.h"

extern "C" {
#include <libavformat/avformat.h>
}

void XData::clear() {
    if (!data) {
        return;
    }
    av_packet_free((AVPacket **)(&data));
    data = 0;
    size = 0;
}

void IDemux::main() { // 测试时使用
    while(!isExit) {
        XData data = read();
        if (data.size > 0) {
            notify(data);
        }
    }
}
