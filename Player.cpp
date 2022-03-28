#include "Player.h"
#include <iostream>
using namespace sf;


void Player::Init(int x, int y) {
    m_sprite.setPosition(x, y);

}


void Player:: setRect(){
    //m_sprite.setTextureRect(IntRect(3, 5, m_width, m_height));
    switch (m_dir)
    {

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
    if (m_player_lives == 0){ is_alive = false;}
}



bool Player::GetIsAlive() const {
    return is_alive;
}

void Player::SetIsAlive(bool alive) {
    Player:: is_alive = alive;
}

int Player::GetPlayerLives() const {
    return m_player_lives;
}

void Player::SetPlayerLives(int lives) {
    m_player_lives = lives;
}





