#include "Enemy_tanks.h"

void Enemy_tank::SetStartX(float x){
    start_x=x;
}
void Enemy_tank::SetStartY(float y){
    start_y=y;
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

bool Enemy_tank::GetIsOnTheField() const{
    return IsOnTheField;
}

void Enemy_tank::SetStartCoordinates(float x, float y){
    start_x=x;
    start_y=y;
}
void Enemy_tank::Start_Enemy_Function(Enemy_tank &t1, Enemy_tank &t2, Enemy_tank &t3){
    t1.SetStartCoordinates(0,0);
    t2.SetStartCoordinates(197,0);
    t3.SetStartCoordinates(419,0);
    t1.IsOnTheField=true;
    t2.IsOnTheField=true;
    t3.IsOnTheField=true;
    t1.Init(t1.start_x, t1.start_y);
    t2.Init(t2.start_x, t2.start_y);
    t3.Init(t3.start_x, t3.start_y);
    t1.SetX(0);
    t1.SetY(0);
    t2.SetX(197);
    t2.SetY(0);
    t3.SetX(419);
    t3.SetY(0);
    t1.SetSpeed(0.1);
    t2.SetSpeed(0);
    t3.SetSpeed(0);


}

//void Enemy_tank::Start_Enemy_Function(float x, float y){
//    start_x=0;
//    start_y=0;
//    m_x=0;
//    m_y=0;
////    t.SetX(x);
////    t.SetY(y);
//    IsOnTheField=true;
//}

void Enemy_tank::Update(float time){

    SetDir((rand() % 4+1));
    SetSpeed(0.1);
    setRect();
    update(time);
}