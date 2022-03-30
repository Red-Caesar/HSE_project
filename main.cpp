#include <iostream>
#include <windows.h>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Audio.h"
#include "Game_time.h"
#include "Enemy_tanks.h"
#include "Menu.h"
#include "Types.h"
using namespace sf;

int StartGame(int level){
    RenderWindow window(VideoMode(544, 480), "Tan4iki!");
    MENU page;
    if(!page.menu(window)){
        return EXIT;
    }
    Map map("Background.png");
    map.SetNumberMap(level);
    Player tank("sprite.bmp", 3, 5, 26, 26, "main_tank");
    Player friend_t("sprite.bmp", 3, 133, 26, 26, "friend_tank");
    friend_t.Init(290,420);
    tank.Init(164, 420);
    if (page.TwoPlayers) friend_t.SpawnInit(friend_t.GetX(),friend_t.GetY());
    tank.SpawnInit(tank.GetX(),tank.GetY());
    ///music

    Audio audio;
    Game_time g_time;

    audio.Init();
    audio.playGame();
    audio.playSpawn();

    bool NewBullet = false;
    bool FriendBullet = false;
    bool base_is_damaged = false;
    bool BigFlag = false;
    bool sparkle = false;
    float CurrentFrame = 0;//хранит текущий кадр


    int n_bul = 1;
    if (page.TwoPlayers) n_bul = 2;
    Bullet bul[n_bul];
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    std::uniform_int_distribution<int> dist(0, 4); // Левая и правая граница рандома
    int STATE =1;

    float time_to_go = 0;
    int enemies_number = 9;

    int n_enemies = enemies_number + 2; // Количество танков, позже должно увеличиться до 10(?)
    Enemy_tank t[n_enemies];  //Создаем массив вражеских танков
    Bullet enemy_bul[n_enemies];  //Создаем массив вражеских пуль с расчетом 1 пуля на 1 танк
    int enemy_iterator = 0;

    Icon enemy_icon("sprite.bmp", 48, 273, 16);
    Icon lives_icon("sprite.bmp", 33, 273, 16);
    Icon friend_lives_icon("sprite.bmp", 33, 273, 16);
    Icon bonus_icon("sprite.bmp", 32, 392, 30);

    /////////////////главный цикл открытого окна//////////////////////////////

    float tank_speed = 0.1;
    int randomX = 0;
    int randomY = 0;
    int bonus_f = 0;
    int bonus_f_f = 0;
    int cur_tank_lives = 0;
    int cur_friend_tank_lives = 0;


    while (window.isOpen()) {
        std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count()); //для рандома
        g_time.Init();
        Event event;
        while (window.pollEvent(event)) {if (event.type == Event::Closed) window.close(); }

        CurrentFrame += 0.005*g_time.GetTime(); //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (CurrentFrame > 2) CurrentFrame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.

        if (tank.GetIsAlive() && (!base_is_damaged)){
            tank.Control(CurrentFrame);
            if (Keyboard::isKeyPressed(Keyboard::LControl)) { NewBullet = true;}
        }else if(!page.end_menu(window) ){
            return GAME_OVER;
        }
        if (page.TwoPlayers){
            if (friend_t.GetIsAlive() && (!base_is_damaged)){
                friend_t.Control(CurrentFrame);
                if (Keyboard::isKeyPressed(Keyboard::Space)) { FriendBullet = true;}
            }
        }
        ///////////////////////////////////////////

        //обработка пуль главного танка

        if (NewBullet) {
            if (!bul[0].Is_On_f) {
                bul[0].Is_On_f = true;
                audio.playShoot();
                bul[0].New_Coordinates_and_Dir(tank);
            }
        }
        if (page.TwoPlayers){
            if (FriendBullet) {
                if (!bul[1].Is_On_f) {
                    bul[1].Is_On_f = true;
                    audio.playShoot();
                    bul[1].New_Coordinates_and_Dir(friend_t);
                }
            }
        }

        NewBullet = false;
        FriendBullet = false;

        window.clear();

/////////////////////////////Рисуем карту/////////////////////

        map.DrawMapBack(window);

        //спауним врагов на поле

        time_to_go += g_time.GetTime();

        if (time_to_go > 3000 and enemy_iterator < n_enemies - 1) {
            time_to_go = 0;
            sparkle = false;
            enemies_number--;
            int class_of_enemy = ENEMY_SLOW;
            if (enemy_iterator > 3){
                std::uniform_int_distribution<int> dist(1,4);
                switch (dist(engine)) {
                    case 1:
                        class_of_enemy = ENEMY_MEDIUM;
                        break;
                    case 2:
                        class_of_enemy = ENEMY_FAST;
                        break;
                    case 4:
                        if (enemy_iterator > 5) class_of_enemy = ENEMY_BIG;
                        break;
                }
            }

            t[enemy_iterator].SetEnemyFile("sprite.bmp", class_of_enemy);
            enemy_bul[enemy_iterator].SetFile("heart.bmp");

            Start_Enemy_Function(t[enemy_iterator]);
            enemy_iterator ++;
        }

        int icons_counter = enemies_number;
        for (int i = 0; i < 3; i++) {
            if (icons_counter<0)
                break;
            for (int j = 0; j < 3; j++) {
                enemy_icon.CreateIcon(464 + j * 24, 64 + i * 24);
                window.draw(enemy_icon.icon_sprite);
                icons_counter--;
                if (icons_counter<0)
                    break;
            }
        }

        for (int i = 0; i < tank.GetPlayerLives(); i++){
            lives_icon.CreateIcon(464 + i * 24, 200);
            window.draw(lives_icon.icon_sprite);
        }

        if (page.TwoPlayers){
            for (int i = 0; i < friend_t.GetPlayerLives(); i++){
                friend_lives_icon.CreateIcon(464 + i * 24, 250);
                friend_lives_icon.icon_sprite.setColor(sf::Color::Green);
                window.draw(friend_lives_icon.icon_sprite);
            }
        }


        //пересечение пуль нашего танка
        if ((enemies_number == 6) and (bonus_f == 0)){
            randomX = 0;
            randomY = 0;
            srand(time(0));//рандом
            randomX = 32 + rand() % (384);
            randomY = 32 + rand() % (384);
            bonus_f = 1;
            bonus_icon.CreateIcon(randomX, randomY);
        }
        if(bonus_f == 1) window.draw(bonus_icon.icon_sprite);

        if(bonus_f == 1 and (tank.GetX() >= randomX-16 ) and (tank.GetX() <= randomX+16) and (tank.GetY() >= randomY - 16) and (tank.GetY() <= randomY+16)){
            audio.playBones();
            bonus_f = 2;
            cur_tank_lives = tank.GetPlayerLives();
        }
        if (bonus_f == 2)
            if(cur_tank_lives == tank.GetPlayerLives()){
                tank_speed = 0.2;
                tank.m_level = 1;
                //tank.SetPlayerLevel(1);
                for (int i = 0; i < n_bul; i++){
                    bul[i].speed = 0.4;}
            }
            else {
                bonus_f = 0;
                tank_speed = 0.1;
                tank.m_level = 0;
                for (int i = 0; i < n_bul; i++) {
                    bul[i].speed = 0.2;
                }
            }

        if (page.TwoPlayers){
            if((bonus_f == 1 and friend_t.GetX() >= randomX-16 ) and (friend_t.GetX() <= randomX+16) and (friend_t.GetY() >= randomY - 16) and (friend_t.GetY() <= randomY+16)){
                audio.playBones();
                bonus_f = 3;
                cur_friend_tank_lives = friend_t.GetPlayerLives();
            }
            if(bonus_f == 3)
                if(cur_friend_tank_lives == friend_t.GetPlayerLives()){
                    tank_speed = 0.2;
                    friend_t.m_level = 1;
                    for (int i = 0; i < n_bul; i++) {
                        bul[i].speed = 0.4;}
                }
                else{
                    bonus_f = 0;
                    tank_speed = 0.1;
                    friend_t.m_level = 0;
                    for (int i = 0; i < n_bul; i++) {
                        bul[i].speed = 0.2;}
                }
        }

        for (int i = 0; i < n_bul; i++) {
            for (int j = 0; j<enemy_iterator; j++) {

                if ( bul[i].Is_On_f && bul[i].GetRect().intersects(enemy_bul[j].GetRect()) && enemy_bul[j].Is_On_f){
                    bul[i].Is_On_f = false;
                    bul[i].SetSpeed(0);
                }

                if (bul[i].Is_On_f && bul[i].GetRect().intersects(t[j].GetRect()) && t[j].GetIsAlive()){
                    bul[i].Is_On_f = false;
                    bul[i].SetSpeed(0);
                }

            }
            if (bul[i].GetIsBaseDamaged()){
                base_is_damaged = true;
            }
            if (bul[i].Is_On_f) {
                bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),bul[i]);
                bul[i].update(g_time.GetTime());
                window.draw(bul[i].sprite);//рисуем спрайт пули
            }
        }

        ///////////////Общий цикл врагов///////////////////////

        for (int i = 0;i<enemy_iterator;i++) {   //Общий цикл врагов
            for (int j = 0; j < n_bul; j++) {
                if (enemy_bul[i].GetRect().intersects(bul[j].GetRect()) && bul[j].Is_On_f && bul[i].Is_On_f) {
                    enemy_bul[i].Is_On_f = false;
                    enemy_bul[i].SetSpeed(0);
                }
            }

            for (int j = 0; j < n_bul; j++) {
                if (t[i].GetRect().intersects(bul[j].GetRect()) && bul[j].Is_On_f && t[i].GetIsAlive()) {
                    t[i].SetIsAlive(false);
                    bul[j].Is_On_f = false;
                    enemy_bul[i].Is_On_f = false;
                }
            }

            if (t[i].GetIsAlive()) {
                map.InteractionEnemyTankWithMap(map.GetDiagramMap(), t[i]);

                if (t[i].GetFlag_to_change()) {      //Если флаг сигнализирует о том, что надо поменять направление
                    t[i].UpdateDir(engine);    // меняем направление
                    t[i].SetFlag_to_change(false);  //Опускаем флаг
                }
                if (!enemy_bul[i].Is_On_f) {     //Если пуля врага была не на поле
                    enemy_bul[i].Is_On_f = true;   // Сделать ее на поле
                    enemy_bul[i].New_Coordinates_and_Dir_Enemy(t[i]); // Установить ей координаты и направление
                }
//
                std::uniform_int_distribution<int> dist(1, 1024);
                switch (dist(engine)) {
                    case 512:
                        t[i].UpdateDir(engine);
                        break;
                }
                if (enemy_bul[i].GetIsBaseDamaged()) {
                    base_is_damaged = true;
                }

                enemy_bul[i].update(g_time.GetTime());   //Обновляем по времени
                enemy_bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),enemy_bul[i]); //Проверяем не попала ли куда-нибудь пуля
                window.draw(enemy_bul[i].sprite);
                t[i].EnemyUpdate(g_time.GetTime(), CurrentFrame);
                if (t[i].GetIsOnTheField()) {
                    t[i].SetSpeed(t[i].GetSpeed());
                }
                window.draw(t[i].GetSprite());
            }
        }

        map.InteractionTankWithMap(map.GetDiagramMap(), tank);
        if (page.TwoPlayers) map.InteractionTankWithMap(map.GetDiagramMap(), friend_t);

        for (int i = 0;i < enemy_iterator; i++) {                                                                                                            enemy_bul[i].Is_On_f;
            if (enemy_bul[i].GetRect().intersects(tank.GetRect()) && enemy_bul[i].Is_On_f ) {
                tank.DecreaseLives();
                tank.Respawn();
                tank.SetFlagSpawn(true);

            }
            if (tank.GetRect().intersects(t[i].GetRect()) && t[i].GetIsAlive()){
                tank.SetSpeed(0);
            }
            if (page.TwoPlayers){
                if (enemy_bul[i].GetRect().intersects(friend_t.GetRect()) && enemy_bul[i].Is_On_f ) {
                    friend_t.DecreaseLives();
                    friend_t.Respawn();
                }
                if (friend_t.GetRect().intersects(t[i].GetRect()) && t[i].GetIsAlive()){
                    friend_t.SetSpeed(0);
                }
            }
        }

        tank.update(g_time.GetTime()); //обновление главного танка
        if (page.TwoPlayers) friend_t.update(g_time.GetTime());
        window.draw(tank.GetSprite());
        if (page.TwoPlayers) if (friend_t.GetIsAlive())window.draw(friend_t.GetSprite());

        if(tank.GetFlagSpawn()){
            tank.SpawnInit (tank.GetX(),tank.GetY());
            if(g_time.GetTimeSpawn() < 1000){
                tank.DrawSpawn(g_time);
                window.draw(tank.GetSpriteSpawn());
                g_time.updateSpawn();
            }else{
                tank.SetFlagSpawn(false);
                g_time.SetTimeSpawn(0);
            }
        }
        if (page.TwoPlayers){
            if(friend_t.GetFlagSpawn()){
                friend_t.SpawnInit (friend_t.GetX(),friend_t.GetY());
                if(g_time.GetTimeSpawn() < 1000){
                    friend_t.DrawSpawn(g_time);
                    window.draw(friend_t.GetSpriteSpawn());
                    g_time.updateSpawn();
                }else{
                    friend_t.SetFlagSpawn(false);
                    g_time.SetTimeSpawn(0);
                }
            }
        }

        map.DrawMapForward(window);
        window.display();
    }
}

int main() {
    int level = 1;
    int state_of_game;
    while(true){
    state_of_game = StartGame(level);
        switch (state_of_game){
            case GAME_OVER: StartGame(1); break;
            case LVL_UP:
                if (level < 3)
                    StartGame(++level);
                else
//                    панелька с победой
            case EXIT: return 0;
        }
    }

    return 0;
}