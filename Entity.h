//
// Created by 79101 on 28.03.2022.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


class Entity {
protected:
    float m_x, m_y, m_speed, m_vx, m_vy;
    int m_width, m_height, m_dir;
    bool is_alive;
    String m_file;
    String m_name;
    Image m_image;
    Sprite m_sprite;
    Texture m_texture;
public:
    Entity(const String& F, float X, float Y, int W, int H, const String name);
    Entity();
    float GetX(); void SetX(float x);

    float GetY(); void SetY(float y);

    float GetSpeedX(); void SetSpeedX(float vx);

    float GetSpeedY(); void SetSpeedY(float vy);

    float GetSpeed(); void SetSpeed(float speed);

    int GetH(); void SetH(int height);

    int GetW(); void SetW(int width);

    int GetDir(); void SetDir(int dir);

    Sprite GetSprite();

    FloatRect GetRect();

    bool GetIsAlive() const;

    void SetIsAlive(bool flag);

};


#endif //GAME_ENTITY_H
