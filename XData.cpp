//
// Created by he li on 12/6/19.

extern "C" {
#include <libavcodec/avcodec.h>
}
//
#include "XData.h"

bool XData::alloc(int size, const unsigned char *data) {
    this->clear();
    type = UCHAR_TYPE;
    if (size < 0) {
        return false;
    }
    this->data = new unsigned char[size];
    if (!this->data) {
        return false;
    }
    if (data) {
        memcpy(this->data, data, size);
    }
    this->size = size;
    return true;
}


void XData::clear() {
    if (!data) {
        return;
    }
    if (type == AVPACKET_TYPE) {
        av_packet_free((AVPacket **) (&data));
    } else {
        delete data;
    }
    data = 0;
    size = 0;
}