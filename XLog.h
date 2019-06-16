//
// Created by he li on 12/6/19.
//
#include <iostream>
using namespace std;
#ifndef XPLAY_XLOG_H
#define XPLAY_XLOG_H


class XLog {
public:
};
#define XLog(tag, str) cout << tag << " : " << str << endl;

#endif //XPLAY_XLOG_H
