//
// Created by he li on 16/6/19.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "list"
#include "mutex"
#include "XParameter.h"
#include "IObserver.h"

class IDecode : public IObserver {
public:
    // 打开解码器 isHard表示是否使用硬解，默认不需要
    virtual bool open(XParameter parameter, bool isHard = false) = 0;

    virtual void close() = 0;

    virtual void clear();

    // future 模型，发送数据到线程解码
    virtual bool sendPacket(XData pkt) = 0;
    // 从线程中获取解码数据的接口 再次调用回复用上次空间，线程不安全
    virtual XData receiveFrame() = 0;

    // 主体调用观察者传递数据，阻塞
    virtual void update(XData data);

    bool isAudio = false;

    // 最大的队列缓冲
    int maxPackets = 100;

    int syncPts = 0; // 同步时间，以音频为基准，再次打开数据要清理

    int pts = 0; // 当前已经解码的pts

protected:
    virtual void main();

    // 读取到的缓冲
    std::list<XData> packets;
    std::mutex packetMutex;
};


#endif //XPLAY_IDECODE_H
