#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Enemy_tanks.h"

using namespace sf;

void draw_map(Map &map, RenderWindow &window){
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++) {
            map.CreateMap(map.GetDiagramMap(), i, j);
            window.draw(map.GetMapSprite());//рисуем квадратики на экран
        }
}

int main() {
    RenderWindow window(VideoMode(448, 416), "Tan4iki!");
    Map map("Background.png");
    map.SetNumberMap(1);
    Player tank("sprite.bmp", 20, 380, 26, 26);

    bool NewBullet = false;

    Clock clock;

    int n_bul = 1;
    Bullet bul[n_bul];
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    int n_enemies = 3;
    Enemy_tank t[n_enemies];

    for (int i=0;i<n_enemies;i++){
        t[i].SetFile("sprite.bmp");
    }
    t[1].Start_Enemy_Function(t[0],t[1],t[2]);



    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        // Обрабатываем очередь событий в цикле
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();}

        if (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) { tank.SetDir(1); tank.SetSpeed(0.1); tank.setRect();}
        if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) { tank.SetDir(0);tank.SetSpeed(0.1);tank.setRect();}
        if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) { tank.SetDir(3); tank.SetSpeed(0.1); tank.setRect(); }
        if (Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) { tank.SetDir(2); tank.SetSpeed(0.1); tank.setRect();}
        if ((Keyboard::isKeyPressed(Keyboard::Space))) { NewBullet = true; }
        ///////////////////////////////////////////

        if (NewBullet) {
            for (int i = 0; i < n_bul; i++) {  // Добавление новой пули
                if (!bul[i].Is_On_f) {
                    bul[i].Is_On_f = true;
                    bul[i].New_Coordinates_and_Dir(tank);
                    break;
                }
            }
            NewBullet = false;
        }

        tank.update(time);
        map.InteractionTankWithMap(map.GetDiagramMap(), tank);
        //!!!
        for (int i=0;i<n_enemies;i++) {
            if(t[i].GetIsOnTheField()) {
                map.InteractionTankWithMap(map.GetDiagramMap(), tank);
            }
        }
        window.clear();

/////////////////////////////Рисуем карту/////////////////////
        draw_map(map,window);
       // window.draw(map.GetMapSprite());
        for (int i = 0; i < n_bul; i++) {
            if (bul[i].Is_On_f) {
                bul[i].update(time);
                bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),bul[i]);
                window.draw(bul[i].sprite);//рисуем спрайт пули
            }
        }
        for (int i=0;i<n_enemies;i++){
            //if(t[i].GetIsAlive() && t[i].GetIsOnTheField()){
//                t[i].update(time);
                window.draw(t[i].GetSprite());
           // }
        }

        window.draw(tank.GetSprite());
        window.display();
    }
    return 0;
}