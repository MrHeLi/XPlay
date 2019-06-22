//
// Created by he li on 16/6/19.
//

#ifndef XPLAY_XPARAMETER_H
#define XPLAY_XPARAMETER_H



struct AVCodecParameters;
class XParameter {
public:
    AVCodecParameters *codecParameters = 0;
    int channels = 2;
    int sample_rate = 0;
//    int sample_rate = 44100;
};


#endif //XPLAY_XPARAMETER_H
