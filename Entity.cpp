#include "Entity.h"
#include <SFML/Graphics.hpp>
Entity::Entity(const String &F, float X, float Y, int W, int H, const String name){
    m_file = F;
    m_vx= 0;
    m_vy = 0;
    m_x = 0;m_y = 0; m_speed = 0;
    m_width = W;
    m_height = H;
    m_name = name;
    is_alive = true;


    m_image.loadFromFile("..\\images/" + m_file);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта.
    m_texture.loadFromImage(m_image);//закидываем наше изображение в текстуру
    m_sprite.setTexture(m_texture);//заливаем спрайт текстурой
    m_sprite.setTextureRect(IntRect(X, Y, m_width, m_height));
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
    m_y = y;
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
    m_vy = vy;
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

Entity::Entity() {

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

FloatRect Entity::GetRect() {
    return FloatRect(m_x, m_y, m_width, m_height);
}

bool Entity::GetIsAlive() const {
    return is_alive;
}

void Entity::SetIsAlive(bool flag){
    is_alive = flag;
}
