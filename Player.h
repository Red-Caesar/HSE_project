#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
    friend class Bullet;
public:
    Player();
    Player(const String F, float X, float Y, int W, int H);
    void Init(int x, int y);
    void update(float time);

    void SetFile(String F);
    double GetSpeed();
    int GetX();
    int GetY();
    int GetSpeedX();
    int GetSpeedY();
    void SetSpeed(float speed);
    void SetX(int x);
    void SetY(int y);
    void SetSpeedX(int vx);
    void SetSpeedY(int vy);
    int GetDir();
    void SetDir(int dir);
    Sprite GetSprite();
    void setRect();
    ///
    //void SetWidth(int w);


private:
    int m_dir = 0;
    int m_width;
    int m_height;
    bool IsAlive = true;
    bool IsOnMap = false;
    Image m_image;
    Sprite m_sprite;
    Texture m_texture;
    //
    String File;
    float m_speed;         //базовая скорость
    float m_x, m_y;        //позиция игрока
    float m_vx, m_vy;      //скорость игрока (ускорение по x и y)
    double m_speed_ratio;   //коэффициент скорости
    double m_bullet_speed;  //скорость пули
    int m_bullet_power;     //сила пули

    int m_lifes; //кол-во жизней

    int  m_tank_width; //высота и ширина в пикселях
    int m_tank_height;


};

#endif