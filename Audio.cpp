//
// Created by NP on 26.03.2022.
//

#include "Audio.h"


void Audio::Init() {

    ShootBuf.loadFromFile("..\\audio/Bullet01_shot.wav");
    Shoot.setBuffer(ShootBuf);

    game.openFromFile("..\\audio/game.wav");
}

void Audio::playGame() {
    game.play();
    game.setLoop(true);
}

void Audio::playShoot() {
    Shoot.play();
}
