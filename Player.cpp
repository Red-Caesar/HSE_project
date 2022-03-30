#include "Player.h"
#include "Types.h"
#include <iostream>
using namespace sf;


void Player::Init(int x, int y) {
    m_sprite.setPosition(x, y);
    m_x = x;
    m_y = y;
    m_dir = DIR_UP;
}


void Player:: setRect(float CurrentFrame){
    //m_sprite.setTextureRect(IntRect(3, 5, m_width, m_height));
    if (m_name == "main_tank"){
        switch (m_dir)
        {
            case DIR_RIGHT: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 1, 35, 26, 26));
                break;
            case DIR_LEFT: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 5, 99, 26, 26));
                break;
            case DIR_DOWN: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 65, 26, 26));
                break;
            case DIR_UP: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 5, 26, 26));
                break;
        }
    }
    if (m_name == "friend_tank"){
        switch (m_dir)
        {
            case DIR_RIGHT: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 1, 163, 26, 26)); break;
            case DIR_LEFT: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 5, 227, 26, 26));break;
            case DIR_DOWN: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 193, 26, 26));break;
            case DIR_UP: m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 133, 26, 26));break;
        }
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
    m_sprite.setPosition(m_x,m_y); //выводим спрайт в позицию x y, посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    if (m_player_lives == 0){ is_alive = false;}
}

int Player::GetPlayerLives() const {
    return m_player_lives;
}

void Player::SetPlayerLives(int lives) {
    m_player_lives = lives;
}

void Player::DecreaseLives(){
    m_player_lives--;
    //is_just_lost_life = true;
}

void Player::Respawn(){
    m_x = 164;
    m_y = 420;
}

bool Player::IsJustLostLife(){
    return is_just_lost_life;
}

void Player::SpawnInit(int x, int y) {
    spawn_image.loadFromFile("..\\images/sprite.bmp");
    spawn_texture.loadFromImage(spawn_image);
    spawn_sprite.setTexture(spawn_texture);
    spawn_sprite.setPosition(x,y);
    Spawn = true;
}

Sprite Player::GetSpriteSpawn() {
    return spawn_sprite;
}

void Player::DrawSpawnStars(Game_time time) {
    int i = time.GetTimeSpawn() / 100;
    switch (i) {
        case 1:
            spawn_sprite.setTextureRect(IntRect(256,32,32,32));
            break;
        case 2:
            spawn_sprite.setTextureRect(IntRect(290,32,32,32));
            break;
        case 3:
            spawn_sprite.setTextureRect(IntRect(320,32,32,32));
            break;
        case 4:
            spawn_sprite.setTextureRect(IntRect(352,32,32,32));
            break;
        case 5:
            spawn_sprite.setTextureRect(IntRect(386,32,32,32));
            break;
        case 6:
            spawn_sprite.setTextureRect(IntRect(420,32,32,32));
            break;
    }

}

void Player::DrawSpawn(Game_time time) {
    int i = time.GetTimeSpawn() / 100;
    i = i%2;
    switch (i) {
        case 0:
            spawn_sprite.setTextureRect(IntRect(256,0,32,32));
            break;
        case 1:
            spawn_sprite.setTextureRect(IntRect(288,0,32,32));
            break;
    }

}

void Player::SetFlagSpawn(bool value){
    Spawn = value;
}
bool Player::GetFlagSpawn(){
    return Spawn;
}

