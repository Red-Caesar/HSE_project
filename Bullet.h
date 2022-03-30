#ifndef GAME_BULLET_H
#define GAME_BULLET_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy_tanks.h"
using namespace sf;

class Bullet {
private:
    float x, y, w, h, dx, dy;
public:
    float speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0; //направление (direction) движения игрока
    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт
    bool Is_On_f = false;

    Bullet();
    //  Bullet(Player &player, String F)
    void update(float time);
    void  New_Coordinates_and_Dir(Player &player);
    void New_Coordinates_and_Dir_Enemy(Enemy_tank &enemy);
    void SetFile(String F);

    float GetX() const;

    float GetY() const;

    float GetH() const;

    float GetW() const;

    float GetSpeedX() const;

    float GetSpeedY() const;

    void SetX(int cur_x);

    void SetY(int cur_y);

    void BonusSpeed(Player &player);

    void SetSpeed(float S);

};


#endif //GAME_BULLET_H