//
// Created by NP on 28.03.2022.
//

#include "Game_time.h"

void Game_time::Init() {

    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time /1000;

}

float Game_time::GetTime() {
    return time;
}
