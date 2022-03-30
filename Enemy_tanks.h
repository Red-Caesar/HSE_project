#ifndef GAME_ENEMY_TANKS_H
#define GAME_ENEMY_TANKS_H
#include <random>
#include "Entity.h"
#include "Game_time.h"

class Enemy_tank : public Entity{
    friend void Start_Enemy_Function(Enemy_tank &t,float r_time);
    friend class Bullet;
private:
    int enemy_class;
    float start_x;
    float start_y;
    bool IsOnTheField;
    // bool IsPlayer=false;
    bool Flag_to_change;//Флаг показывающий, что пора сменить направление
    float respawn;
    int period;
public:
    //Enemy_tank(const String &F, float X, float Y, int W, int H, const String name) : Entity(F,X, Y, W, H, name){
      //  IsOnTheField=false;
     //   Flag_to_change=true;
  //  }
    Enemy_tank(){

    }


    void EnemyUpdate(float time, float CurrentFrame);
    void SetEnemyFile(String F, int class_of_enemy);
    //void Update(float time);
    void UpdateDir(std::mt19937 engine);
    void SetStartX(float x);
    void SetStartY(float y);
    float GetStartX() const;
    float GetStartY() const;
    //bool GetIsAlive() const;
    bool GetIsOnTheField() const;
    void SetIsOnTheField(bool flag);
    void SetStartCoordinates(float x, float y);
    void SetRespawnTime(float time);
    void Start_Enemy_Function(Enemy_tank &t,float r_time);
    void EnemyInit(int x, int y);
    void SetEnemyRect(float CurrentFrame);
    //bool SetIsPlayer(bool f);

    void SetFlag_to_change(bool f);

   //bool GetIsPlayer() const;

    bool GetFlag_to_change() const;


};

#endif //GAME_ENEMY_TANKS_H
