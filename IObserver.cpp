//
// Created by he li on 16/6/19.
//

#include "IObserver.h"

// 主体添加观察者
void IObserver::addObserver(IObserver *observer) {
    if (observer == NULL) {
        return;
    }
    mMutex.lock();
    observers.push_back(observer);
    mMutex.unlock();
}

// 通知所有观察者
void IObserver::notify(XData data) {
    mMutex.lock();
    for (int i = 0; i < observers.size(); i++) {
        observers[i]->update(data);
    }
    mMutex.unlock();
}