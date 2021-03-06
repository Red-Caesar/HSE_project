#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy_tanks.h"

using namespace sf;

class Bullet {
private:
    float x, y, w, h, dx, dy;
    bool is_base_damaged;
public:
    float speed = 0;
    int dir = 0;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    bool Is_On_f = false;

    Bullet();

    void update(float time);

    void New_Coordinates_and_Dir(Player &player);

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

    void SetSpeed(float s_speed);

    void SetIsBaseDamaged(bool flag);

    bool GetIsBaseDamaged();

    FloatRect GetRect();

    void BonusSpeed(Player &player);

};


#endif //GAME_BULLET_H