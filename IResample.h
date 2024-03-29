//
// Created by he li on 19/6/19.
//

#ifndef XPLAY_IRESAMPLE_H
#define XPLAY_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver {
public:
    virtual bool open(XParameter in, XParameter out = XParameter()) = 0;

    virtual void close() = 0;

    virtual XData resample(XData xData) = 0;

    virtual void update(XData xData);

    int outChannels = 2;

    int outFormat = 1;
};


#endif //XPLAY_IRESAMPLE_H
