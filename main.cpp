#include <iostream>
#include <string>
#include "IPlayer.h"
#include "FFPlayerBuilder.h"

using namespace std;

static IPlayer *player = 0;

int main() {
    string source_url = "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4";

    player = FFPlayerBuilder::get()->buildPlayer();
    player->open(source_url.c_str());
    player->start();

    xSleep(300000);
}