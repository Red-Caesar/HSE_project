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
    t2.SetStartCoordinates((12*36-38)/2,0);
    t3.SetStartCoordinates(12*36-13,0);
    t1.IsOnTheField=true;
    t2.IsOnTheField=true;
    t3.IsOnTheField=true;
    t1.Init(t1.start_x, t1.start_y);
    t2.Init(t2.start_x, t2.start_y);
    t3.Init(t3.start_x, t3.start_y);
}
