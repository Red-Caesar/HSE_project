//
// Created by NP on 28.03.2022.
//

#ifndef GAME_GAME_TIME_H
#define GAME_GAME_TIME_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Game_time {
private:
    Clock clock;
    float time ;
public:
    void Init();
    float GetTime();
};


#endif //GAME_GAME_TIME_H
