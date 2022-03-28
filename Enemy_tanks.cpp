#include <random>
#include <stdlib.h>
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
    Flag_to_change = f;
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
    t.SetEnemyX(t.GetStartX());
    t.SetEnemyY(t.GetStartY());
    t.SetEnemySpeed(0);
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
    switch (period) {
        case 1:

            break;
    }
    std::uniform_int_distribution<int> dist(0,3);
    SetEnemyDir(dist(engine));
    SetEnemyRect();
}
