#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
    friend class Bullet;

private:
    int m_dir = 3;
    int m_width = 32;
    int m_height = 32;
    Image m_image;
    Sprite m_sprite;
    Texture m_texture;
    //
    String File;
    String Name;
    float m_speed;         //базовая скорость
    float m_x, m_y;        //позиция игрока
    float m_vx, m_vy;      //скорость игрока (ускорение по x и y)

    int m_player_lives; //кол-во жизней
    bool m_alive; //живой или нет
    bool IsPlayer = true;

public:
    Player(const String &F, float X, float Y, int W, int H);

    Player();

    void Init(int x, int y);

    void update(float time);

    double GetSpeed();

    bool GetAlive() const;

    void SetAlive(bool alive);

    int GetPlayerLives() const;

    void SetPlayerLives(int lives);

    float GetX();

    float GetY();

    float GetSpeedX();

    float GetSpeedY();

    float GetH();

    float GetW();

    void SetSpeed(float speed);

    void SetX(int x);

    void SetY(int y);

    void SetFile(String F);

    void SetSpeedX(int vx);

    void SetSpeedY(int vy);

    int GetDir();

    void SetDir(int dir);

    Sprite GetSprite();

    void setRect();

    void SetW();

    void SetH();
};

#endif