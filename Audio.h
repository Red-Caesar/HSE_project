#ifndef GAME_AUDIO_H
#define GAME_AUDIO_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class Audio {
private:
 SoundBuffer ShootBuf;
 Sound Shoot;

 Music game;
public:
    void Init();
    void playGame();
    void playShoot();
};


#endif //GAME_AUDIO_H
