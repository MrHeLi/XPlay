#include <iostream>
#include <string>
#include "IPlayerProxy.h"

using namespace std;
int main() {
    string source_url = "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4";
    IPlayerProxy::get()->init();
    IPlayerProxy::get()->open(source_url.c_str());
    IPlayerProxy::get()->start();

    xSleep(300000);
}