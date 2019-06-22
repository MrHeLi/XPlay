//
// Created by he li on 16/6/19.
//

#include "IDecode.h"
#include "XLog.h"

// 主体调用观察者传递数据
void IDecode::update(XData data) { // 生产者
    if (data.isAudio != isAudio) {
        return;
    }

    while(!isExit) {
        packetMutex.lock();
        if (packets.size() < maxPackets) {
            packets.push_back(data);
            packetMutex.unlock();
            break;
        }
        packetMutex.unlock();
        xSleep(1); // 阻塞
    }
}

void IDecode::main() { // 消费者
    while(!isExit) {
        packetMutex.lock();

        // 音视频同步判断
        if (!isAudio && syncPts > 0) {
            XLog(syncPts, pts);
            if (syncPts < pts) {
                packetMutex.unlock();
                xSleep(1);
                continue;
            }
        }

        if (packets.empty()) {
            packetMutex.unlock();
            xSleep(1);
            continue;
        }
        XData data = packets.front();
        packets.pop_front();

        if (this->sendPacket(data)) { // 发送到解码队列
            while (!isExit) {
                // 获取解码数据
                XData frame = receiveFrame();
                if (!frame.data) {
                    break;
                }
                pts = frame.pts;
//                XLog("receiveFrame size = ", frame.size);
                // 发送数据给观察者
                this->notify(frame);
            }
        }
        data.clear();
        packetMutex.unlock();
    }
}