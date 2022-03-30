#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;

class Player : public Entity{
    friend class Bullet;

private:

    int m_player_lives; //кол-во жизней
    int m_score; //счет игрока
    bool is_just_lost_life; //только что отняли жизнь

public:
    Player(const String& F, float X, float Y,int W,int H, const String name) : Entity(F,X,Y,W,H,name){
        m_player_lives = 3;
        m_score = 0;
        is_just_lost_life = false;
    }


    void Init(int x, int y);

    void update(float time);

    void SetIsAlive(bool alive);

    int GetPlayerLives() const;

    void SetPlayerLives(int lives);

    void setRect(float CurrentFrame);

    void DecreaseLives();

    void Respawn();

    bool IsJustLostLife();




};

#endif