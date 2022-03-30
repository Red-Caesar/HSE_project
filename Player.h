#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game_time.h"

using namespace sf;

class Player : public Entity{
    friend class Bullet;

private:
    Image spawn_image;
    Sprite spawn_sprite;
    Texture spawn_texture;
    bool Spawn = true;
    int m_player_lives; //кол-во жизней
    int m_score; //счет игрока
public:
    int m_level = 0;
    Player(const String& F, float X, float Y,int W,int H, const String name) : Entity(F,X,Y,W,H,name){
        m_player_lives = 3;
        m_score = 0;
    }

    void Init(int x, int y);

    void update(float time);

    void SetIsAlive(bool alive);

    int GetPlayerLives() const;

    void SetPlayerLives(int lives);

    void setRect(float CurrentFrame);

    void DecreaseLives();

    void Respawn();

    void SpawnInit(int x, int y);

    Sprite GetSpriteSpawn();

    void DrawSpawnStars(Game_time time);

    void DrawSpawn(Game_time time);

    void SetPlayerLevel(int level);

    void SetFlagSpawn(bool value);

    bool GetFlagSpawn();

    void Control(float CurrentFrame);

};

#endif