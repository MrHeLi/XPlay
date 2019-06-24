#include <iostream>
#include <string>
#include <thread>
#include "IPlayerProxy.h"

using namespace std;
int main() {
    string source_url_1 = "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4";
    string source_url_2 = "/Users/heli/Desktop/output.mp4";
    string source_url_3 = "/Users/heli/Desktop/economics.mp4";
    IPlayerProxy::get()->init();
    IPlayerProxy::get()->open(source_url_3.c_str());
    IPlayerProxy::get()->start();


    IPlayerProxy::get()->open(source_url_2.c_str());
    IPlayerProxy::get()->start();

    xSleep(300000);
}