#include <chrono>
#include "Game.h"
#include "Map.h"
#include "Audio.h"
#include "Menu.h"
#include "Types.h"

void GlobalUpdate(Player &tank, Game_time &g_time, Map &map, int &enemy_iterator, Enemy_tank t[], Bullet enemy_bul[],
                  float &time_to_go, int &enemies_number, int &n_enemies, std::mt19937 &engine){
    tank.update(g_time.GetTime());
    map.InteractionTankWithMap(map.GetDiagramMap(), tank);
    for (int i = 0; i < enemy_iterator; i++) {
        //if(t[i].GetIsOnTheField()) { //Для ситуации когда танков всего больше, чем на поле
        map.InteractionEnemyTankWithMap(map.GetDiagramMap(), t[i]);
        // }
    }
    if (time_to_go > 3000 and enemy_iterator < n_enemies - 1) {
        time_to_go = 0;
        enemies_number--;
        int class_of_enemy = ENEMY_SLOW;
        if (enemy_iterator > 3) {
            std::uniform_int_distribution<int> dist(1, 4);
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
        enemy_iterator++;
    }
}

void GlobalDrawing(RenderWindow &window, Map &map, int enemies_number, Icon &enemy_icon, Player &tank, Icon &lives_icon,
                    Bullet bul[],int n_bul, Game_time &g_time){

    for (int i = 0; i < HEIGHT_MAP; i++) {//Рисуем карту
        for (int j = 0; j < WIDTH_MAP; j++) {
            map.CreateMap(map.GetDiagramMap(), i, j);
            window.draw(map.GetMapSprite());//рисуем квадратики на экран
        }

    }
    int icons_counter = enemies_number;
    for (int i = 0; i < 3; i++) {
        if (icons_counter < 0)
            break;
        for (int j = 0; j < 3; j++) {
            enemy_icon.CreateIcon(464 + j * 24, 64 + i * 24);
            window.draw(enemy_icon.icon_sprite);
            icons_counter--;
            if (icons_counter < 0)
                break;
        }
    }

    for (int i = 0; i < tank.GetPlayerLives(); i++) {
        lives_icon.CreateIcon(464 + i * 24, 200);
        window.draw(lives_icon.icon_sprite);
    }
    for (int i = 0; i < n_bul; i++) {
        if (bul[i].Is_On_f) {
            bul[i].update(g_time.GetTime());
            bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(), bul[i]);
            window.draw(bul[i].sprite);//рисуем спрайт пули
        }
    }
    window.draw(tank.GetSprite());
}

bool WorkingWithKeyboard(Player &tank){
    bool NewBullet =false;
    if (tank.GetAlive()) {
        if (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) {
            tank.SetDir(DIR_LEFT);
            tank.SetSpeed(0.1);
            tank.setRect();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) {
            tank.SetDir(DIR_RIGHT);
            tank.SetSpeed(0.1);
            tank.setRect();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) {
            tank.SetDir(DIR_UP);
            tank.SetSpeed(0.1);
            tank.setRect();
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) {
            tank.SetDir(DIR_DOWN);
            tank.SetSpeed(0.1);
            tank.setRect();
        }
        if ((Keyboard::isKeyPressed(Keyboard::Space))) { NewBullet = true; }
    }
    return NewBullet;
}

void CreateNewBullet(int n_bul, Bullet bul[], Player &tank) {
    for (int i = 0; i < n_bul; i++) {  // Добавление новой пули
        if (!bul[i].Is_On_f) {
            bul[i].Is_On_f = true;
            bul[i].New_Coordinates_and_Dir(tank);
            break;
        }
    }
}

void EnemyUpdateAndDraw(Game_time &g_time, int &enemy_iterator, Enemy_tank t[], Bullet enemy_bul[], std::mt19937 &engine, Map &map, RenderWindow &window){
    for (int i = 0; i < enemy_iterator; i++) {   //Общий цикл врагов
        //if(t[i].GetIsAlive() && t[i].GetIsOnTheField()){  // Возможно пригодится для добавления новых танков
        if (t[i].GetFlag_to_change()) {      //Если флаг сигнализирует о том, что надо поменять направление
            t[i].UpdateDir(engine);    // меняем направление
            t[i].SetFlag_to_change(false);  //Опускаем флаг
        }
        if (!enemy_bul[i].Is_On_f) {     //Если пуля врага была не на поле
            enemy_bul[i].Is_On_f = true;   // Сделать ее на поле
            enemy_bul[i].New_Coordinates_and_Dir_Enemy(t[i]); // Установить ей координаты и направление
        }
        std::uniform_int_distribution<int> dist(1, 1024);
        switch (dist(engine)) {
            case 512:
                t[i].UpdateDir(engine);
                break;
        }
        enemy_bul[i].update(g_time.GetTime());   //Обновляем по времени
        enemy_bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),
                                                            enemy_bul[i]); //Проверяем не попала ли куда-нибудь пуля
        window.draw(enemy_bul[i].sprite); //Рисуем пулю
        t[i].EnemyUpdate(g_time.GetTime());
        if (t[i].GetIsOnTheField()) {  //Если пуля на поле, то устанавливаем ей скорость
            t[i].SetEnemySpeed(0.05);
        }
        window.draw(t[i].GetEnemySprite());
        // }
    }
}

void Reset(int STATE, Player &tank,Enemy_tank t[]){
   //switch(STATE){
       //case 1:{
           Map map("Background.png");
           map.SetNumberMap(STATE);
           tank.SetX(164);
           tank.SetY(420);
           int enemies_number = 9;
           for (int i=0;i<enemies_number;i++){
               Start_Enemy_Function(t[i],0);
           }
       }
       //case 2:
       //case 3:
    //       ;
   //}
//}

bool Game(RenderWindow &window) {
    int STATE = 1;

    Audio audio;
    Game_time g_time;

    audio.Init();
    audio.playGame();
    audio.playSpawn();

    bool NewBullet = false;

    int n_bul = 1;
    Bullet bul[n_bul];
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    std::uniform_int_distribution<int> dist(0, 4); // Левая и правая граница рандома

    float time_to_go = 0;
    int enemies_number = 9; //!??!?!??!?!? Вводить при переходе на новый уровень?
    int n_enemies = enemies_number + 2;
    //!?!?!??!?!?!?!?!

    Enemy_tank t[n_enemies];  //Создаем массив вражеских танков
    Bullet enemy_bul[n_enemies];  //Создаем массив вражеских пуль с расчетом 1 пуля на 1 танк
    int enemy_iterator = 0;
    Map map("Background.png");
    map.SetNumberMap(1);

    Icon enemy_icon("sprite.bmp", 48, 273);
    Icon lives_icon("sprite.bmp", 33, 273);

    while(1) {
        switch (STATE) {
            case 0: {
                if (!end_menu(window)) {
                    return 0;
                }
                STATE = 1;
                break;
            }
            case 1:
            case 2:
            case 3:
            {
                Player tank("sprite.bmp", 164, 420, 26, 26);
                map.SetNumberMap(STATE);
                while (window.isOpen()) {

                    std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count()); //для рандома
                    g_time.Init(); //Для таймера(?)

                    Event event; // Обрабатываем очередь событий в цикле
                    while (window.pollEvent(event)) {
                        if (event.type == Event::Closed) {
                            window.close();
                            return false;
                        }
                    }

                    NewBullet=WorkingWithKeyboard(tank);
                    if (NewBullet) {
                        CreateNewBullet(n_bul, bul, tank);
                        audio.playShoot();
                    }

                    time_to_go += g_time.GetTime();
                    GlobalUpdate(tank, g_time, map, enemy_iterator, t, enemy_bul, time_to_go, enemies_number, n_enemies, engine);

                    GlobalDrawing(window, map, enemies_number, enemy_icon, tank, lives_icon, bul, n_bul, g_time);

                    EnemyUpdateAndDraw(g_time, enemy_iterator, t, enemy_bul, engine, map, window);

                    window.display();
                    window.clear();

                    if (enemies_number == 0) {  //Условия на переход на новый уровень
                        if (STATE < 3) {
                            STATE += 1;
                            enemies_number = 9;
                            n_enemies = enemies_number + 2;
                            Reset(STATE,tank,t);
                        } else {
                            STATE = 0;
                        }
                        break;
                    }
//                if(tank.GetPlayerLives()==0){  //Условия на Game Over
//                    STATE=0;
//                }
                }
                break;
            }
        }
    }
    return true;
};