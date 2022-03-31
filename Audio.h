#ifndef GAME_AUDIO_H
#define GAME_AUDIO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Audio {
private:
    SoundBuffer ShootBuf;
    SoundBuffer BonesBuf;
    SoundBuffer SpawnBuf;
    Sound Shoot;
    Sound Bones;
    Sound Spawn;

    Music game;
    Music menu;
public:
    void Init();

    void playGame();

    void playShoot();

    void playMenu();

    void playBones();

    void playSpawn();
};


#endif //GAME_AUDIO_H
