#include <random>
#include <stdlib.h>
#include "Types.h"
#include "Enemy_tanks.h"

void Enemy_tank::SetEnemyFile( String F, int class_of_enemy) {
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
            m_speed = 0.01;
            break;
        case ENEMY_MEDIUM:
            top = 616;
            m_speed = 0.01;
            break;
        case ENEMY_FAST:
            top = 744;
            m_speed = 0.2;
            break;
        case ENEMY_BIG:
            top = 872;
            m_speed = 0.01;
            break;
    }
    is_alive = true;
    m_sprite.setTextureRect(IntRect(3, top, m_width, m_height));
}
void Enemy_tank::SetStartX(float x){
    start_x=x;
}
void Enemy_tank::SetStartY(float y){
    start_y=y;
}

void Enemy_tank::SetFlag_to_change(bool f) {
    Flag_to_change = f;
}

float Enemy_tank::GetStartX() const{
    return start_x;
}
float Enemy_tank::GetStartY() const{
    return start_y;
}

bool Enemy_tank::GetFlag_to_change() const{
    return Flag_to_change;
}

void Enemy_tank::SetIsOnTheField(bool flag){
    IsOnTheField = flag;
}

bool Enemy_tank::GetIsOnTheField() const{
    return IsOnTheField;
}

void Enemy_tank::SetStartCoordinates(float x, float y){
    start_x = x;
    start_y = y;
}
void Enemy_tank::SetRespawnTime(float time){
    respawn = time;
}
void Enemy_tank::EnemyInit(int x, int y){
    m_sprite.setPosition(x, y);
}
void Enemy_tank::EnemyUpdate(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
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

}
void Start_Enemy_Function(Enemy_tank &t, float r_time){   //Расставляем первые 3 танка, возможно надо сделать подобную, но поменьше для каждого нового танка
    srand(time(NULL));
    int random = 1 + rand()%9;
    switch (random) {
        case 1: case 4: case 7:
            t.SetStartCoordinates(32,32);
            break;
        case 2: case 5: case 8:
            t.SetStartCoordinates(229,32);
            break;
        case 3: case 6: case 9:
            t.SetStartCoordinates(451,32);
            break;
    }
    t.SetRespawnTime(r_time);
    t.period = 1;
    t.SetIsOnTheField(true);
    t.EnemyInit(t.GetStartX(), t.GetStartY());
    t.SetX(t.GetStartX());
    t.SetY(t.GetStartY());
    t.SetSpeed(0);
}

void Enemy_tank::SetEnemyRect(){
    switch (enemy_class) {
        case ENEMY_SLOW:
            switch (m_dir)
            {
                case DIR_RIGHT: m_sprite.setTextureRect(IntRect(0, 459, 30, 26)); break;
                case DIR_LEFT: m_sprite.setTextureRect(IntRect(2, 523, 30, 26));break;
                case DIR_DOWN: m_sprite.setTextureRect(IntRect(3, 488, 26, 30));break;
                case DIR_UP: m_sprite.setTextureRect(IntRect(3, 426, 26, 30));break;
            }
            break;
        case ENEMY_MEDIUM:
            switch (m_dir)
            {
                case DIR_RIGHT: m_sprite.setTextureRect(IntRect(0, 587, 30, 26)); break;
                case DIR_LEFT: m_sprite.setTextureRect(IntRect(2, 651, 30, 26));break;
                case DIR_DOWN: m_sprite.setTextureRect(IntRect(3, 616, 26, 30));break;
                case DIR_UP: m_sprite.setTextureRect(IntRect(3, 554, 26, 30));break;
            }
            break;
        case ENEMY_FAST:
            switch (m_dir)
            {
                case DIR_RIGHT: m_sprite.setTextureRect(IntRect(0, 715, 30, 26)); break;
                case DIR_LEFT: m_sprite.setTextureRect(IntRect(2, 779, 30, 26));break;
                case DIR_DOWN: m_sprite.setTextureRect(IntRect(3, 744, 26, 30));break;
                case DIR_UP: m_sprite.setTextureRect(IntRect(3, 682, 26, 30));break;
            }
            break;
        case ENEMY_BIG:
            switch (m_dir)
            {
                case DIR_RIGHT: m_sprite.setTextureRect(IntRect(0, 843, 30, 26)); break;
                case DIR_LEFT: m_sprite.setTextureRect(IntRect(2, 907, 30, 26));break;
                case DIR_DOWN: m_sprite.setTextureRect(IntRect(3, 872, 26, 30));break;
                case DIR_UP: m_sprite.setTextureRect(IntRect(3, 810, 26, 30));break;
            }
            break;
    }
}

void Enemy_tank::UpdateDir(std::mt19937 engine){  // Добавляем "случайное" направление
    std::uniform_int_distribution<int> dist(0,3);
    SetDir(dist(engine));
    SetEnemyRect();
}
