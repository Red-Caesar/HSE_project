#ifndef GAME_BULLET_H
#define GAME_BULLET_H
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Bullet {
public:
    float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
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
    void SetFile(String F);
};


#endif //GAME_BULLET_H
