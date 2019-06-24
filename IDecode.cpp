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
//            XLog(syncPts, pts);
            // 1. 目前还是没法实现同步，原因如下：
            //    1）音频同步时间更新是在重采样后，加入到frameList缓冲的pts，即使从解码到播放，中间有三个缓冲减小速度，速度非常快。
            //       最终使syncPts总是大于视频播放时间。无法启到显示视频速度的作用。
            //    2）但音频实际播放速度远没有这么快。syncPts时间的更新最好是音频播放时更新。
            //    解一：当前代码无法得知数据的播放时间，只能通过SDL的音频回调函数才能确定。但因为一个异常尚无法使用，解决这个异常即可。
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
                pts = frame.pts; // frame.pts 这里是解码后的pts
                // 发送数据给观察者
                this->notify(frame);
            }
        }
        data.clear();
        packetMutex.unlock();
    }
}

void IDecode::clear() {
    packetMutex.lock();
    while (!packets.empty()) {
        packets.front().clear();
        packets.pop_front();
    }
    pts = 0;
    syncPts = 0;
    packetMutex.unlock();
}