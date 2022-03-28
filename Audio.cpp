//
// Created by NP on 26.03.2022.
//

#include "Audio.h"


void Audio::Init() {

    ShootBuf.loadFromFile("..\\audio/Bullet01_shot.wav");
    Shoot.setBuffer(ShootBuf);

    BonesBuf.loadFromFile("..\\audio/Bonus_take.wav");
    Bones.setBuffer(BonesBuf);

    SpawnBuf.loadFromFile("..\\audio/Spawn.wav");
    Spawn.setBuffer(SpawnBuf);

    game.openFromFile("..\\audio/game.wav");
    menu.openFromFile("..\\audio/menu.wav");


}

void Audio::playGame() {
    game.play();
    game.setLoop(true);
}

void Audio::playShoot() {
    Shoot.play();
}

void Audio::playMenu() {
    menu.play();
    menu.setLoop(true);
}

void Audio::playBones() {
    Bones.play();
}

void Audio::playSpawn() {
    Spawn.play();
}
