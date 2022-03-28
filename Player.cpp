#include "Player.h"
#include <iostream>
using namespace sf;

double Player::GetSpeed()
{
    return m_speed;
}


float Player::GetX()
{
    return m_x;
}


float Player::GetY()
{
    return m_y;
}

float Player::GetSpeedX()
{
    return m_vx;
}

float Player::GetSpeedY()
{
    return m_vy;
}
float Player::GetH() {
    return m_height;
}
float Player::GetW() {
    return m_width;
}

void Player::Init(int x, int y) {
    m_sprite.setPosition(x, y);
    //m_speed = 5.5;

    //m_can_shoot = true;
    //m_bullets_in_game = 0;

    //m_start_x = x;  m_start_y = y;

    //SetPlayerLevel(0);
}


Player::Player(const String& F, float X, float Y, int W, int H) {
    {
        File = F;
        m_x= X;
        m_y = Y;
        m_width = W;
        m_height = H;
        m_player_lives = 3;
        m_alive = true;

        m_image.loadFromFile("..\\images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
        //m_image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
        m_texture.loadFromImage(m_image);//закидываем наше изображение в текстуру
        m_sprite.setTexture(m_texture);//заливаем спрайт текстурой
        m_sprite.setTextureRect(IntRect(3, 5, m_width, m_height));
        m_sprite.setPosition(m_x,m_y);

    }
}

Player::Player() {
    {
        m_width = 26;
        m_height = 26;
    }
}

void Player::SetFile(String F){
    File = F;
    m_image.loadFromFile("..\\images/" + File);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(IntRect(3, 5, m_width, m_height));

}

void Player::SetSpeed(float speed) {
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
void Player::SetW() {
    {
        m_width = 26;
        m_height = 26;
    }
}
void Player::SetH() {
    {
        m_height = 26;
    }
}

Sprite Player::GetSprite() {
    return m_sprite;
}

void Player:: setRect(){
    //m_sprite.setTextureRect(IntRect(3, 5, m_width, m_height));
    switch (m_dir)
    {
        /*case 0: m_sprite.setRotation(90);  m_sprite.setPosition(m_x,m_y);  break;
        case 1: m_sprite.setRotation(-90); break;
        case 2: m_sprite.setRotation(180); break;
        case 3: m_sprite.setRotation(0); break; */

        case 0: m_sprite.setTextureRect(IntRect(1, 35, 26, 26)); break;
        case 1: m_sprite.setTextureRect(IntRect(5, 99, 26, 26));break;
        case 2: m_sprite.setTextureRect(IntRect(3, 65, 26, 26));break;
        case 3: m_sprite.setTextureRect(IntRect(3, 5, 26, 26));break;


    }
}



void Player::update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    switch (m_dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
    {
        case 0: m_vx = m_speed; m_vy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1: m_vx = -m_speed; m_vy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2: m_vx = 0; m_vy = m_speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 3: m_vx = 0; m_vy = -m_speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
    }

    m_x += m_vx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
    m_y += m_vy*time;//аналогично по игреку

    m_speed = 0;//зануляем скорость, чтобы персонаж остановился.
    m_sprite.setPosition(m_x,m_y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    if (m_player_lives == 0){ m_alive = false;}
}

int Player::GetDir() {
return m_dir;
}

void Player::SetDir(int dir) {
m_dir = dir;
}

bool Player::GetAlive() const {
    return m_alive;
}

void Player::SetAlive(bool alive) {
    Player:: m_alive = alive;
}

int Player::GetPlayerLives() const {
    return m_player_lives;
}

void Player::SetPlayerLives(int lives) {
    m_player_lives = lives;
}





