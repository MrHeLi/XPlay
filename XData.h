//
// Created by he li on 12/6/19.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H

enum XDataType {
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};

class XData {
public:
    int type = 0;
    int pts = 0;
    unsigned char *data = 0;
    int size = 0;
    bool isAudio = false;
    int width;
    int height;
    int format = 0;
    bool alloc(int size, const unsigned char *data = 0);
    void clear();
};


#endif //XPLAY_XDATA_H
