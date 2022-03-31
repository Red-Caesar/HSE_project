#include "Bullet.h"
#include "Types.h"

Bullet::Bullet() {
    w = 7.0;
    h = 7.0;
    x = 0;
    y = 0;
    dir = 0;
    speed = 0.1;
    sprite.setTextureRect(IntRect(156, 27, w,h));
    is_base_damaged = false;
}

void Bullet::update(float time) {
    switch (dir) {
        case 0:
            dx = speed;
            dy = 0;
            break;
        case 1:
            dx = -speed;
            dy = 0;
            break;
        case 2:
            dx = 0;
            dy = speed;
            break;
        case 3:
            dx = 0;
            dy = -speed;
            break;
    }
    x += dx * time;
    y += dy * time;

    if (x >= 32 * 17 || y >= 32 * 15 || x <= 32 || y <= 32) {
        speed = 0;
        Is_On_f = false;
    } else {
        sprite.setPosition(x, y);
    }
}

void Bullet::New_Coordinates_and_Dir(Player &player) {
    dir = player.GetDir();
    x = player.GetX() + 10;
    y = player.GetY() + 10;
    speed = 0.2;
}

void Bullet::New_Coordinates_and_Dir_Enemy(Enemy_tank &enemy) {
    dir = enemy.GetDir();
    x = enemy.GetX() + 10;
    y = enemy.GetY() + 10;
    speed = 0.2;
    switch (enemy.enemy_class) {
        case ENEMY_MEDIUM:
            speed = 0.3;
            break;
    }
}

void Bullet::SetFile(String F) {
    File = F;
    image.loadFromFile("..\\images/" + File);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

float Bullet::GetX() const {
    return x;
}

float Bullet::GetY() const {
    return y;
}

float Bullet::GetSpeedX() const {
    return dx;
}

float Bullet::GetSpeedY() const {
    return dy;
}

void Bullet::SetSpeed(float s_speed) {
    speed = s_speed;
}

void Bullet::SetX(int cur_x) {
    x = cur_x;
}

void Bullet::SetY(int cur_y) {
    y = cur_y;
}

float Bullet::GetH() const {
    return h;
}

float Bullet::GetW() const {
    return w;
}


FloatRect Bullet::GetRect() {
    return FloatRect(x, y, w, h);
}

void Bullet::SetIsBaseDamaged(bool flag) {
    is_base_damaged = flag;
}

bool Bullet::GetIsBaseDamaged() {
    return is_base_damaged;
}