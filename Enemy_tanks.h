
#ifndef GAME_ENEMY_TANKS_H
#define GAME_ENEMY_TANKS_H
#include <random>
#include "Player.h"

class Enemy_tank : public Player{
private:
    float start_x;
    float start_y;
    bool IsAlive=true;
    bool IsOnTheField=false;
   // bool IsPlayer=false;
    bool Flag_to_change=true; //Флаг показывающий, что пора сменить направление

public:
    //Enemy_tank(const String &F, float X, float Y, int W, int H) : Player(F,X, Y, W, H){}
    //Enemy_tank() : Player(){}
    Enemy_tank();
    //void Update(float time);
    void UpdateDir(float time,std::mt19937 engine);
    void SetStartX(float x);
    void SetStartY(float y);
    float GetStartX() const;
    float GetStartY() const;
    bool GetIsAlive() const;
    bool GetIsOnTheField() const;
    void SetStartCoordinates(float x, float y);
    void Start_Enemy_Function(Enemy_tank &t1, Enemy_tank &t2, Enemy_tank &t3);

    //bool SetIsPlayer(bool f);

    bool SetFlag_to_change(bool f);

   //bool GetIsPlayer() const;

    bool GetFlag_to_change() const;

    bool SetIsAlive(bool f);
};

#endif //GAME_ENEMY_TANKS_H
