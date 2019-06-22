//
// Created by da li on 22/6/19.
//

#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"

bool IPlayerProxy::open(const char *path) {
    int result = false;
    proxyMutex.lock();
    if (player) {
        result = player->open(path);
    }
    proxyMutex.unlock();
    return result;
}

bool IPlayerProxy::start() {
    bool result = false;
    proxyMutex.lock();
    if (player) {
        result = player->start();
    }
    proxyMutex.unlock();
    return result;
}

void IPlayerProxy::init() {
    proxyMutex.lock();
    if (!player) {
        player = FFPlayerBuilder::get()->buildPlayer();
    }
    proxyMutex.unlock();
}