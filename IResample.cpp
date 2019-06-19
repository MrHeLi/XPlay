//
// Created by he li on 19/6/19.
//

#include "IResample.h"

void IResample::update(XData xData) {
    XData data = this->resample(xData);
    if (data.size > 0) {
        this->notify(data);
    }
}