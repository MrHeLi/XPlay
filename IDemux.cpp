//
// Created by he li on 12/6/19.
//

#include "IDemux.h"
#include "XLog.h"


void IDemux::main() { // 测试时使用
    while(!isExit) {
        XData data = read();
        if (data.size > 0) {
            notify(data);
        }
    }
}
