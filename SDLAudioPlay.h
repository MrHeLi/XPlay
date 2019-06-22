//
// Created by he li on 19/6/19.
//

#ifndef XPLAY_SDLAUDIOPLAY_H
#define XPLAY_SDLAUDIOPLAY_H


#include "IAudioPlay.h"

class SDLAudioPlay : public IAudioPlay {
public:
    virtual bool startPlay(XParameter out);

    void fill_audio(void *udata, uint8_t *stream, int len);
protected:
    void run();
};


#endif //XPLAY_SDLAUDIOPLAY_H
