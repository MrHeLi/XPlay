//
// Created by he li on 19/6/19.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    virtual void update(XData data);
    virtual bool startPlay(XParameter out) = 0;
};


#endif //XPLAY_IAUDIOPLAY_H
