#ifndef GAME_ENEMY_TANKS_H
#define GAME_ENEMY_TANKS_H
#include <random>
#include "Entity.h"
#include "Game_time.h"

class Enemy_tank : public Entity{
    friend void Start_Enemy_Function(Enemy_tank &t);
    friend class Bullet;
private:
    int enemy_class;
    float start_x;
    float start_y;
    bool IsOnTheField;
    bool Flag_to_change;//Флаг показывающий, что пора сменить направление
    float respawn;
    int period;
public:
    Enemy_tank(){

    }
    void EnemyUpdate(float time, float CurrentFrame);
    void SetEnemyFile(String F, int class_of_enemy);
    void UpdateDir(std::mt19937 engine);
    void SetStartX(float x);
    void SetStartY(float y);
    float GetStartX() const;
    float GetStartY() const;
    bool GetIsOnTheField() const;
    void SetIsOnTheField(bool flag);
    void SetStartCoordinates(float x, float y);
    void SetRespawnTime(float time);
    void Start_Enemy_Function(Enemy_tank &t);
    void EnemyInit(int x, int y);
    void SetEnemyRect(float CurrentFrame);
    void SetFlag_to_change(bool f);
    bool GetFlag_to_change() const;

};

#endif //GAME_ENEMY_TANKS_H
