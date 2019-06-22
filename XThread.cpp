
#include <iostream>
#include "thread"
#include "XThread.h"
#include "XLog.h"

using namespace std;

void xSleep(int ms) {
    chrono::milliseconds duration(ms);
    this_thread::sleep_for(duration);
}

void XThread::run() {
    XLog("XThread", "run_begin");
    isRunning = true;
    main();
    isRunning = false;
    XLog("XThread", "run_end");
}

// 启动线程
bool XThread::start() {
    isExit = false;
    thread th1(&XThread::run, this);
    th1.detach();
    return true;
}

// 通过isExit安全停止线程（不一定成功）
void XThread::stop() {
    isExit = true;
    for (int i = 0; i < 200; ++i) {
        if (!isRunning) {
            XLog("XThread", "thread exit success")
            return;
        }
        xSleep(1);
    }
    XLog("XThread", "thread exit timeout")
}