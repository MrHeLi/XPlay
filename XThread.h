//
// Created by he li on 12/6/19.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

void xSleep(int ms);

class XThread {
public:
    // 启动线程
    virtual void start();

    // 通过isExit安全停止线程（不一定成功）
    virtual void stop();

    // 入口函数
    virtual void main() {}

protected:
    bool isExit = false;
    bool isRunning = false;

private:
    void run();
};


#endif //XPLAY_XTHREAD_H
