//
// Created by he li on 19/6/19.
//

#ifndef XPLAY_FFRESAMPLE_H
#define XPLAY_FFRESAMPLE_H


#include "IResample.h"

struct SwrContext;

class FFResample : public IResample {
public:
    virtual bool open(XParameter in, XParameter out = XParameter());

    virtual void close();

    virtual XData resample(XData inData);

protected:
    SwrContext *aCtx = 0;

    std::mutex resampleMutex;
};


#endif //XPLAY_FFRESAMPLE_H
