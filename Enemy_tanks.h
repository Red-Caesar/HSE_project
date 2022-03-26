
#ifndef GAME_ENEMY_TANKS_H
#define GAME_ENEMY_TANKS_H

#include "Player.h"

class Enemy_tank : public Player{
private:
    float start_x;
    float start_y;
    bool IsAlive=true;
    bool IsOnTheField=false;


public:
    Enemy_tank(const String &F, float X, float Y, int W, int H) : Player(F,X, Y, W, H){}
    Enemy_tank() : Player(){}
    void Update(float time);
    void SetStartX(float x);
    void SetStartY(float y);
    float GetStartX() const;
    float GetStartY() const;
    bool GetIsAlive() const;
    bool GetIsOnTheField() const;
    void SetStartCoordinates(float x, float y);
    void Start_Enemy_Function(Enemy_tank &t1, Enemy_tank &t2, Enemy_tank &t3);
    //void Start_Enemy_Function(Enemy_tank &t, float x, float y);
    //void Start_Enemy_Function(float x, float y);
};

#endif //GAME_ENEMY_TANKS_H
