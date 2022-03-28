#include <random>
#include "Enemy_tanks.h"


Enemy_tank::Enemy_tank() {
    {
        SetW();
        SetH();
    }
}
float Enemy_tank::GetEnemyX()
{
    return e_x;
}


float Enemy_tank::GetEnemyY()
{
    return e_y;
}

void Enemy_tank::SetEnemyX(int x)
{
    e_x = x;
}


void Enemy_tank::SetEnemyY(int y)
{
    e_y = y;
}

float Enemy_tank::GetEnemySpeedX()
{
    return e_vx;
}

float Enemy_tank::GetEnemySpeedY()
{
    return e_vy;
}

float Enemy_tank::GetEnemyH() {
    return e_height;
}
float Enemy_tank::GetEnemyW() {
    return e_width;
}

int Enemy_tank::GetEnemyDir() {
    return e_dir;
}
Sprite Enemy_tank::GetEnemySprite() {
    return e_sprite;
}

void Enemy_tank::SetEnemyFile(String F, int class_of_enemy) {
    enemy_class = class_of_enemy;
    File = F;
    e_image.loadFromFile("..\\images/" + File);
    e_texture.loadFromImage(e_image);
    e_sprite.setTexture(e_texture);
    switch (enemy_class) {
        case 0:
            e_width = 26;
            e_height = 30;
            e_sprite.setTextureRect(IntRect(3, 488, e_width, e_height));
            e_dir = 2;
            e_speed = 0.1;
            break;
    }


}
void Enemy_tank::SetStartX(float x){
    start_x=x;
}
void Enemy_tank::SetStartY(float y){
    start_y=y;
}
bool Enemy_tank::SetIsAlive(bool f) {
    IsAlive = f;
}
bool Enemy_tank::SetFlag_to_change(bool f) {
    Flag_to_change=f;
}

void Enemy_tank::SetEnemySpeed(float speed) {
    e_speed = speed;
}

float Enemy_tank::GetStartX() const{
    return start_x;
}
float Enemy_tank::GetStartY() const{
    return start_y;
}
bool Enemy_tank::GetIsAlive() const{
    return IsAlive;
}
bool Enemy_tank::GetFlag_to_change() const{
    return Flag_to_change;
}

bool Enemy_tank::GetIsOnTheField() const{
    return IsOnTheField;
}

void Enemy_tank::SetStartCoordinates(float x, float y){
    start_x = x;
    start_y = y;
}
void Enemy_tank::EnemyInit(int x, int y){
    e_sprite.setPosition(x, y);
}
void Enemy_tank::EnemyUpdate(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
    switch (e_dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
    {
        case 0: e_vx = e_speed; e_vy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1: e_vx = -e_speed; e_vy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2: e_vx = 0; e_vy = e_speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 3: e_vx = 0; e_vy = -e_speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
    }

    e_x += e_vx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
    e_y += e_vy*time;//аналогично по игреку

    e_speed = 0;//зануляем скорость, чтобы персонаж остановился.
    e_sprite.setPosition(e_x,e_y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.

}
void Start_Enemy_Function(Enemy_tank &t1, Enemy_tank &t2, Enemy_tank &t3){   //Расставляем первые 3 танка, возможно надо сделать подобную, но поменьше для каждого нового танка
    t1.SetStartCoordinates(32,32);
    t2.SetStartCoordinates(229,32);
    t3.SetStartCoordinates(451,32);
    t1.IsOnTheField = true;
    t2.IsOnTheField = true;
    t3.IsOnTheField = true;
    t1.EnemyInit(t1.start_x, t1.start_y);
    t2.EnemyInit(t2.start_x, t2.start_y);
    t3.EnemyInit(t3.start_x, t3.start_y);
    t1.e_x = 32;
    t1.e_y = 32;
    t2.e_x = 229;
    t2.e_y = 32;
    t3.e_x = 451;
    t3.e_y = 32;
    t1.e_speed = 0;
    t2.e_speed = 0;
    t3.e_speed = 0;
}
void Enemy_tank::SetEnemyDir(int new_dir){
    e_dir = new_dir;
}
void Enemy_tank::SetEnemyRect(){
    switch (e_dir)
    {
        case 0: e_sprite.setTextureRect(IntRect(0, 459, 30, 26)); break;
        case 1: e_sprite.setTextureRect(IntRect(2, 523, 30, 26));break;
        case 2: e_sprite.setTextureRect(IntRect(3, 488, 26, 30));break;
        case 3: e_sprite.setTextureRect(IntRect(3, 426, 26, 30));break;


    }
}

void Enemy_tank::UpdateDir(float time,std::mt19937 engine){  // Добавляем "случайное" направление
        std::uniform_int_distribution<int> dist(0,3);
        SetEnemyDir(dist(engine));
        SetEnemyRect();
}
