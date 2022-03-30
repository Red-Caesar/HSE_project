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


int main() {

    RenderWindow window(VideoMode(544, 480), "Tan4iki!");
    if(!menu(window)){
        return 0;
    }
   /* if(!end_menu(window)){
        return 0;
    }*/

    //////////инициализация переменных////////////////////
    Map map("Background.png");
    map.SetNumberMap(1);
    Player tank("sprite.bmp", 3, 5, 26, 26, "main_tank");
    tank.Init(164, 420);
    ///music

    Audio audio;
    Game_time g_time;

    audio.Init();
    audio.playGame();
    audio.playSpawn();

    bool NewBullet = false;
    bool base_is_damaged = false;
    bool BigFlag = false;
    float CurrentFrame = 0;//хранит текущий кадр


    int n_bul = 1;
    Bullet bul[n_bul]; // массив пуль главного танка
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    std::uniform_int_distribution<int> dist(0, 4); // Левая и правая граница рандома
    int STATE =1;

    float time_to_go = 0;
    int enemies_number = 2;

    int n_enemies = enemies_number + 2; // Количество танков, позже должно увеличиться до 10(?)
    Enemy_tank t[n_enemies];  //Создаем массив вражеских танков
    Bullet enemy_bul[n_enemies];  //Создаем массив вражеских пуль с расчетом 1 пуля на 1 танк
    int enemy_iterator = 0;

    Icon enemy_icon("sprite.bmp", 48, 273);
    Icon lives_icon("sprite.bmp", 33, 273);



    /////////////////главный цикл открытого окна//////////////////////////////

    while (window.isOpen()) {
        std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count()); //для рандома
          g_time.Init();

        // Обрабатываем очередь событий в цикле
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();}
        if (tank.GetIsAlive() && (!base_is_damaged)){
            if (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) { tank.SetDir(DIR_LEFT); tank.SetSpeed(0.1); tank.setRect();}
            if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) { tank.SetDir(DIR_RIGHT);tank.SetSpeed(0.1);tank.setRect();}
            if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) { tank.SetDir(DIR_UP); tank.SetSpeed(0.1); tank.setRect(); }
            if (Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) { tank.SetDir(DIR_DOWN); tank.SetSpeed(0.1); tank.setRect();}
            if ((Keyboard::isKeyPressed(Keyboard::Space))) { NewBullet = true;}
        }
        else  if(!end_menu(window)){
        return 0;
        }

        ///////////////////////////////////////////

        //обработка пуль главного танка

        if (NewBullet) {
            for (int i = 0; i < n_bul; i++) {  // Добавление новой пули
                if (!bul[i].Is_On_f) {
                    bul[i].Is_On_f = true;
                    audio.playShoot();
                    bul[i].New_Coordinates_and_Dir(tank); //привязываем пулю к направлению главного танка
                    break;
                }
            }
        }
        NewBullet = false;


        //обновление главного танка
      //  for (int i = 0; i<enemy_iterator; i++) {


        window.clear();

/////////////////////////////Рисуем карту/////////////////////

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++) {
                map.CreateMap(map.GetDiagramMap(), i, j);
                window.draw(map.GetMapSprite());//рисуем квадратики на экран
            }
       // window.draw(map.GetMapSprite());

       //спауним врагов на поле

        time_to_go += g_time.GetTime();
        if (time_to_go > 3000 and enemy_iterator < n_enemies - 1) {
            time_to_go = 0;
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

            Start_Enemy_Function(t[enemy_iterator], g_time.GetTime());
            enemy_iterator ++;
        }



        //рисуем иконки врагов и жизней

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


        //пересечение пуль нашего танка

        for (int i = 0; i < n_bul; i++) {
            for (int j = 0; j<enemy_iterator; j++) {

                //if (bul[i].GetRect().intersects(enemy_bul[j].GetRect())){
               // std::cout << bul[i].GetRect().intersects(enemy_bul[j].GetRect()) << "\n";}
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

       // for (int i=0;i<enemy_iterator;i++) {
            //if(t[i].GetIsOnTheField()) { //Для ситуации когда танков всего больше, чем на поле

            // }
       // }

        for (int i = 0;i<enemy_iterator;i++){   //проходимся по врагам

            for (int j = 0; j<n_bul; j++){
                if (enemy_bul[i].GetRect().intersects(bul[j].GetRect()) && bul[j].Is_On_f && bul[i].Is_On_f ){
                    enemy_bul[i].Is_On_f = false;
                    enemy_bul[i].SetSpeed(0);
                }
            }

            for (int j = 0; j<n_bul; j++){
                if (t[i].GetRect().intersects(bul[j].GetRect()) && bul[j].Is_On_f && t[i].GetIsAlive()){
                    //t[i].SetIsOnTheField(false);
                    t[i].SetIsAlive(false);
                    bul[j].Is_On_f = false;
                    enemy_bul[i].Is_On_f = false;
                }
            }
            if (t[i].GetIsAlive()){
                map.InteractionEnemyTankWithMap(map.GetDiagramMap(), t[i]);
                //if(t[i].GetIsAlive() && t[i].GetIsOnTheField()){  // Возможно пригодится для добавления новых танков
                if(t[i].GetFlag_to_change()){      //Если флаг сигнализирует о том, что надо поменять направление
                    t[i].UpdateDir(engine);    // меняем направление
                    t[i].SetFlag_to_change(false);  //Опускаем флаг
                }
                if(!enemy_bul[i].Is_On_f) {     //Если пуля врага была не на поле
                    enemy_bul[i].Is_On_f = true;   // Сделать ее на поле
                    enemy_bul[i].New_Coordinates_and_Dir_Enemy(t[i]); // Установить ей координаты и направление
                }
//           Делаем еще один рандом
//            srand(time(NULL));
//            int random = 1 + rand()%32;
                std::uniform_int_distribution<int> dist(1,1024);
                switch (dist(engine)) {
                    case 512:
                        t[i].UpdateDir(engine);
                        break;
                }

                if (enemy_bul[i].GetIsBaseDamaged()){
                    base_is_damaged = true;
                }


                enemy_bul[i].update(g_time.GetTime());   //Обновляем ПУЛЮ по времени
                enemy_bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(), enemy_bul[i]); //Проверяем не попала ли куда-нибудь пуля
                //if (enemy_bul[i].GetRect().intersects(tank.GetRect()) && enemy_bul[i].Is_On_f) {
                    //enemy_bul[i].Is_On_f = false;
                    //tank.DecreaseLives();
                //}

                window.draw(enemy_bul[i].sprite); //Рисуем пулю
                t[i].EnemyUpdate(g_time.GetTime()); //Обновляем ВРАГА
                if(t[i].GetIsOnTheField()){  //Если пуля на поле, то устанавливаем ей скорость
                    t[i].SetSpeed(0.05);
                }
                window.draw(t[i].GetSprite());
            }

            // }
        }

        map.InteractionTankWithMap(map.GetDiagramMap(), tank);



        for (int i=0;i<enemy_iterator;i++) {
            //if  (enemy_bul[i].GetRect().intersects(tank.GetRect()))
               // std::cout <<  (enemy_bul[i].GetRect().intersects(tank.GetRect())) << " " << enemy_bul[i].Is_On_f << std::endl;                                                                                                               enemy_bul[i].Is_On_f;
            if (enemy_bul[i].GetRect().intersects(tank.GetRect()) && enemy_bul[i].Is_On_f ) {
                tank.DecreaseLives();
                tank.Respawn();

            }
            if (tank.GetRect().intersects(t[i].GetRect()) && t[i].GetIsAlive()){
                tank.SetSpeed(0);
            }
        }

        tank.update(g_time.GetTime()); //обновление главного танка
        window.draw(tank.GetSprite());

        window.display();
    }
    return 0;
}