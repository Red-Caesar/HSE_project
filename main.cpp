#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Audio.h"
#include "Game_time.h"
using namespace sf;


int main() {

    RenderWindow window(VideoMode(544, 480), "Tan4iki!");
    Map map("Background.png");
    map.SetNumberMap(1);
    Player tank("sprite.bmp", 164, 420, 26, 26);
    ///music

    Audio audio;
    Game_time g_time;

    audio.Init();
    audio.playGame();
    audio.playSpawn();


    int Dir = 0;

    bool NewBullet = false;
    bool BigFlag = false;
    float CurrentFrame = 0;//хранит текущий кадр


    int n_bul = 1;
    Bullet bul[n_bul];
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    float time_to_go = 0;
    int enemies_number = 9;


    class Icon {
    public:
        float x, y, w, h, a, b = 0;
        String File;
        Image image;
        Texture icon_texture;
        Sprite icon_sprite;

        Icon(String F, float X, float Y) {
            File = F;
            x = X;
            y = Y;
            // x = 48/33;
            //y = 273;
            w = 16;
            h = 16;
            image.loadFromFile("..\\images/" + File);
            icon_texture.loadFromImage(image);
            icon_sprite.setTexture(icon_texture);
            icon_sprite.setTextureRect(IntRect(x, y, w,h));
        }
        void CreateIcon(int x, int y) {
            // x = 464;
            // y = 64/200;
                icon_sprite.setPosition(x, y);
        }
    };

    Icon enemy_icon("sprite.bmp", 48, 273);
    Icon lives_icon("sprite.bmp", 33, 273);

    while (window.isOpen()) {
          g_time.Init();

        // Обрабатываем очередь событий в цикле
        Event event;


        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();}
        if (tank.GetAlive()){
            if (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) { tank.SetDir(1); tank.SetSpeed(0.1); tank.setRect();}
            if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) { tank.SetDir(0);tank.SetSpeed(0.1);tank.setRect();}
            if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) { tank.SetDir(3); tank.SetSpeed(0.1); tank.setRect(); }
            if (Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) { tank.SetDir(2); tank.SetSpeed(0.1); tank.setRect();}
            if ((Keyboard::isKeyPressed(Keyboard::Space))) { NewBullet = true; }
        }

        ///////////////////////////////////////////

        if (NewBullet) {
            for (int i = 0; i < n_bul; i++) {  // Добавление новой пули
                if (!bul[i].Is_On_f) {
                    bul[i].Is_On_f = true;
                    audio.playShoot();
                    bul[i].New_Coordinates_and_Dir(tank);
                    break;
                }
            }
            NewBullet = false;
        }
        NewBullet = false;
        tank.update(g_time.GetTime());
        map.InteractionTankWithMap(map.GetDiagramMap(), tank);
        window.clear();

/////////////////////////////Рисуем карту/////////////////////

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++) {
                map.CreateMap(map.GetDiagramMap(), i, j);
                window.draw(map.GetMapSprite());//рисуем квадратики на экран
            }
       // window.draw(map.GetMapSprite());
        time_to_go += g_time.GetTime();
        if (time_to_go > 3000) {
            time_to_go = 0;
            enemies_number--;
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


        for (int i = 0; i < n_bul; i++) {
            if (bul[i].Is_On_f) {
                bul[i].update(g_time.GetTime());
                bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),bul[i]);
                window.draw(bul[i].sprite);//рисуем спрайт пули
            }
        }


        window.draw(tank.GetSprite());
        window.display();
    }
    return 0;
}