//
// Created by he li on 19/6/19.
//

#ifndef XPLAY_SDLAUDIOPLAY_H
#define XPLAY_SDLAUDIOPLAY_H


#include "IAudioPlay.h"

class SDLAudioPlay : public IAudioPlay {
public:
    virtual bool startPlay(XParameter out);
};


#endif //XPLAY_SDLAUDIOPLAY_H
