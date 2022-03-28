//
// Created by 79101 on 28.03.2022.
//

#include "Entity.h"
Entity::Entity(const String& F, float X, float Y, int W, int H, const String name){
    m_file = F;
    m_x= X;
    m_y = Y;
    m_width = W;
    m_height = H;
    m_name = name;
   // m_lives = 3;
    is_alive = true;

    m_image.loadFromFile("..\\images/" + m_file);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
    //m_image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
    m_texture.loadFromImage(m_image);//закидываем наше изображение в текстуру
    m_sprite.setTexture(m_texture);//заливаем спрайт текстурой
    m_sprite.setTextureRect(IntRect(X, Y, m_width, m_height));
    //m_sprite.setPosition(m_x,m_y);
}

float Entity::GetX()
{
    return m_x;
}

void Entity::SetX(float x) {
    m_x = x;
}

float Entity::GetY(){
    return m_y;
}

void Entity::SetY(float y) {
    m_x = y;
}

float Entity::GetSpeedX() {
    return m_vx;
}

void Entity::SetSpeedX(float vx) {
    m_vx = vx;
}

float Entity::GetSpeedY() {
    return m_vy;
}

void Entity::SetSpeedY(float vy) {
    m_vx = vy;
}

float Entity::GetSpeed() {
    return m_speed;
}

void Entity::SetSpeed(float speed) {
    m_speed = speed;
}

int Entity::GetH(){
    return m_height;
}

void Entity::SetH(int height){
    m_height = height;
}

int Entity:: GetW(){
    return m_width;
}

void Entity:: SetW(int width){
    m_width = width;
}

int Entity::GetDir() {
    return m_dir;
}

void Entity::SetDir(int dir){
    m_dir = dir;
}

Sprite Entity::GetSprite() {
    return m_sprite;
}