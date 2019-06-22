//
// Created by he li on 22/6/19.
//

#ifndef XPLAY_FFPLAYERBUILDER_H
#define XPLAY_FFPLAYERBUILDER_H


#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder {
public:
    static FFPlayerBuilder *get() {
        static FFPlayerBuilder ff;
        return &ff;
    }

protected:
    FFPlayerBuilder() {}

    virtual IDemux *createDemux();

    virtual IDecode *createDecode();

    virtual IResample *createResample();

    virtual IAudioPlay *createAudioPlay();

    virtual IVideoView *createVideoView();

    virtual IPlayer *createPlayer(unsigned char index = 0);
};


#endif //XPLAY_FFPLAYERBUILDER_H
