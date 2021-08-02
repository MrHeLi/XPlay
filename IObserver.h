//
// Created by he li on 16/6/19.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H

#include "vector"
#include "mutex"
#include "XData.h"
#include "XThread.h"

// 包含了 观察者 和 主体（被观察者）
class IObserver : public XThread {
public:
    // 主体调用观察者传递数据
    virtual void update(XData data) {}

    // 主体添加观察者，线程安全
    void addObserver(IObserver *observer);

    // 通知所有观察者，线程安全
    void notify(XData data);

private:
    std::vector<IObserver *> observers;
    std::mutex mMutex;
};


#endif //XPLAY_IOBSERVER_H
