//
// Created by he li on 19/6/19.
//

#include "IAudioPlay.h"
#include "XLog.h"

XData IAudioPlay::getData() {
    XData data;
    while (!isExit) {
        frameMutex.lock();
        if (!frameList.empty()) {
            data = frameList.front();
            frameList.pop_front();
            frameMutex.unlock();
            return data;
        }
        frameMutex.unlock();
        xSleep(1);
    }
    return data;
}

void IAudioPlay::update(XData data) {
    // 压如缓冲队列
//    XLog("IAudioPlay::update", data.size);
    frameMutex.lock();
    while (data.size > 0) {
        if (frameList.size() > maxFrame) {
            xSleep(1);
            continue;
        }
        frameList.push_back(data);
        frameMutex.unlock();
        break;
    }
}