#include <random>
#include <stdlib.h>
#include "Types.h"
#include "Enemy_tanks.h"

void Enemy_tank::SetEnemyFile(String F, int class_of_enemy) {
    enemy_class = class_of_enemy;
    m_image.loadFromFile("..\\images/" + F);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_width = 26;
    m_height = 30;
    int top;
    m_dir = 2;
    switch (enemy_class) {
        case ENEMY_SLOW:
            top = 488;
            m_speed = 0.05;
            break;
        case ENEMY_MEDIUM:
            top = 616;
            m_speed = 0.05;
            break;
        case ENEMY_FAST:
            top = 744;
            m_speed = 0.1;
            break;
        case ENEMY_BIG:
            top = 872;
            m_speed = 0.05;
            break;
    }
    is_alive = true;
    m_sprite.setTextureRect(IntRect(3, top, m_width, m_height));
}

void Enemy_tank::SetStartX(float x) {
    start_x = x;
}

void Enemy_tank::SetStartY(float y) {
    start_y = y;
}

void Enemy_tank::SetFlag_to_change(bool f) {
    Flag_to_change = f;
}

float Enemy_tank::GetStartX() const {
    return start_x;
}

float Enemy_tank::GetStartY() const {
    return start_y;
}

bool Enemy_tank::GetFlag_to_change() const {
    return Flag_to_change;
}

void Enemy_tank::SetIsOnTheField(bool flag) {
    IsOnTheField = flag;
}

bool Enemy_tank::GetIsOnTheField() const {
    return IsOnTheField;
}

void Enemy_tank::SetStartCoordinates(float x, float y) {
    start_x = x;
    start_y = y;
}

void Enemy_tank::EnemyInit(int x, int y) {
    m_sprite.setPosition(x, y);
}

void Enemy_tank::EnemyUpdate(float time, float CurrentFrame) {
    switch (m_dir) {
        case 0:
            m_vx = m_speed;
            m_vy = 0;
            break;
        case 1:
            m_vx = -m_speed;
            m_vy = 0;
            break;
        case 2:
            m_vx = 0;
            m_vy = m_speed;
            break;
        case 3:
            m_vx = 0;
            m_vy = -m_speed;
            break;
    }

    m_x += m_vx * time;
    m_y += m_vy * time;

    m_sprite.setPosition(m_x, m_y);
    SetEnemyRect(CurrentFrame);
}

void Start_Enemy_Function(Enemy_tank &t) {
    srand(time(NULL));
    int random = 1 + rand() % 9;
    switch (random) {
        case 1:
        case 4:
        case 7:
            t.SetStartCoordinates(32, 32);
            break;
        case 2:
        case 5:
        case 8:
            t.SetStartCoordinates(229, 32);
            break;
        case 3:
        case 6:
        case 9:
            t.SetStartCoordinates(451, 32);
            break;
    }
    t.SetIsOnTheField(true);
    t.EnemyInit(t.GetStartX(), t.GetStartY());
    t.SetX(t.GetStartX());
    t.SetY(t.GetStartY());
}

void Enemy_tank::SetEnemyRect(float CurrentFrame) {
    switch (enemy_class) {
        case ENEMY_SLOW:
            switch (m_dir) {
                case DIR_RIGHT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 0, 459, 30, 26));
                    break;
                case DIR_LEFT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 2, 523, 30, 26));
                    break;
                case DIR_DOWN:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 488, 26, 30));
                    break;
                case DIR_UP:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 426, 26, 30));
                    break;
            }
            break;
        case ENEMY_MEDIUM:
            switch (m_dir) {
                case DIR_RIGHT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 0, 587, 30, 26));
                    break;
                case DIR_LEFT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 2, 651, 30, 26));
                    break;
                case DIR_DOWN:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 616, 26, 30));
                    break;
                case DIR_UP:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 554, 26, 30));
                    break;
            }
            break;
        case ENEMY_FAST:
            switch (m_dir) {
                case DIR_RIGHT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 0, 715, 30, 26));
                    break;
                case DIR_LEFT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 2, 779, 30, 26));
                    break;
                case DIR_DOWN:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 744, 26, 30));
                    break;
                case DIR_UP:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 682, 26, 30));
                    break;
            }
            break;
        case ENEMY_BIG:
            switch (m_dir) {
                case DIR_RIGHT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 0, 843, 30, 26));
                    break;
                case DIR_LEFT:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 2, 907, 30, 26));
                    break;
                case DIR_DOWN:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 872, 26, 30));
                    break;
                case DIR_UP:
                    m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 810, 26, 30));
                    break;
            }
            break;
    }
}

void Enemy_tank::UpdateDir(std::mt19937 engine) {
    std::uniform_int_distribution<int> dist(0, 3);
    SetDir(dist(engine));
}
