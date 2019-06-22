//
// Created by he li on 19/6/19.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H

#include "list"
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    // 缓冲队列满后阻塞
    virtual void update(XData data);
    // 获取队列中数据, 如果没有则阻塞
    virtual XData getData();

    virtual bool startPlay(XParameter out) = 0;

    int maxFrame = 100; // 默认最大缓冲

    int pts = 0;

protected:
    std::list<XData> frameList;
    std::mutex frameMutex; // 队列操作一定要互斥
};


#endif //XPLAY_IAUDIOPLAY_H
