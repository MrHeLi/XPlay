//
// Created by da li on 22/6/19.
//

#ifndef XPLAY_IPLAYERPROXY_H
#define XPLAY_IPLAYERPROXY_H

#include <mutex>
#include "IPlayer.h"

class IPlayerProxy : public IPlayer {
public:
    static IPlayerProxy *get() {
        static IPlayerProxy proxy;
        return &proxy;
    }

    void init();

    virtual bool open(const char *path);

    virtual bool start();

protected:
    IPlayerProxy() {}

    IPlayer *player = 0;
    std::mutex proxyMutex;
};


#endif //XPLAY_IPLAYERPROXY_H
