#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

double Player::GetSpeed()
{
    return m_speed;
}


int Player::GetX()
{
    return m_x;
}


int Player::GetY()
{
    return m_y;
}

int Player::GetSpeedX()
{
    return m_vx;
}

int Player::GetSpeedY()
{
    return m_vy;
}
void Player::Init(int x, int y) {
    m_sprite.setPosition(x, y);
    //m_speed = 5.5;

    //m_can_shoot = true;
    //m_bullets_in_game = 0;

    //m_start_x = x;  m_start_y = y;

    //SetPlayerLevel(0);
}


void Player::Draw(Texture& General_Texture, float left, float top, float width, float height){
//    Texture General_Texture;
//    General_Texture.loadFromFile("..\\images/m_sprite.bmp");

    m_sprite.setTexture(General_Texture);
    m_sprite.setTextureRect(IntRect(left, top, width, height));
//    Если поставить в rectHeight минус, то танк поедет назад

}

void Player::SetSpeed(double speed) {
 m_speed = speed;
}

void Player::SetX(int x) {
m_x = x;
}

void Player::SetY(int y) {
m_y = y;
}

void Player::SetSpeedX(int vx) {
m_vx = vx;
}

void Player::SetSpeedY(int vy) {
m_vy = vy;
}

Sprite Player::GetSprite() {
    return m_sprite;
}

