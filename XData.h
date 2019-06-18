//
// Created by he li on 12/6/19.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


class XData {
public:
    unsigned char *data = 0;
    int size = 0;
    bool isAudio = false;
    void clear();
    int width;
    int height;
};


#endif //XPLAY_XDATA_H
