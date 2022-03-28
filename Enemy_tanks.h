
#ifndef GAME_ENEMY_TANKS_H
#define GAME_ENEMY_TANKS_H
#include <random>
#include "Player.h"

class Enemy_tank : public Player{
    friend void Start_Enemy_Function(Enemy_tank &t);
    friend class Bullet;
private:
    int enemy_class;
    int e_dir;
    Image e_image;
    Sprite e_sprite;
    Texture e_texture;
    String File;
    float start_x;
    float start_y;
    bool IsAlive = true;
    bool IsOnTheField=false;
    float e_speed;         //базовая скорость
    float e_x, e_y;        //позиция игрока
    float e_vx, e_vy;
    // bool IsPlayer=false;
    bool Flag_to_change=true; //Флаг показывающий, что пора сменить направление
    int e_width;
    int e_height;
public:
    //Enemy_tank(const String &F, float X, float Y, int W, int H) : Player(F,X, Y, W, H){}
    //Enemy_tank() : Player(){}
    Enemy_tank();
    float GetEnemyX();

    float GetEnemyY();

    void SetEnemyX(int x);

    void SetEnemyY(int y);

    float GetEnemySpeedX();

    float GetEnemySpeedY();

    float GetEnemyH();

    float GetEnemyW();

    int GetEnemyDir();

    Sprite GetEnemySprite();
    void SetEnemySpeed(float speed);
    void EnemyUpdate(float time);
    void SetEnemyDir(int new_dir);
    void SetEnemyFile(String F, int class_of_enemy);
    //void Update(float time);
    void UpdateDir(float time,std::mt19937 engine);
    void SetStartX(float x);
    void SetStartY(float y);
    float GetStartX() const;
    float GetStartY() const;
    bool GetIsAlive() const;
    bool GetIsOnTheField() const;
    void SetIsOnTheField(bool flag);
    void SetStartCoordinates(float x, float y);
    void Start_Enemy_Function(Enemy_tank &t);
    void EnemyInit(int x, int y);
    void SetEnemyRect();
    //bool SetIsPlayer(bool f);

    bool SetFlag_to_change(bool f);

   //bool GetIsPlayer() const;

    bool GetFlag_to_change() const;

    bool SetIsAlive(bool f);
};

#endif //GAME_ENEMY_TANKS_H
