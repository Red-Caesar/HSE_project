#include <chrono>
#include "Game.h"
#include "Map.h"
#include "Audio.h"
#include "Menu.h"
#include "Types.h"

bool WorkingWithKeyboardPlayer1(Player &tank, MENU page, float CurrentFrame){
    bool NewBullet =false;
    if (tank.GetIsAlive()) {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            tank.SetDir(DIR_LEFT);
            tank.SetSpeed(0.1);
            tank.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            tank.SetDir(DIR_RIGHT);
            tank.SetSpeed(0.1);
            tank.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            tank.SetDir(DIR_UP);
            tank.SetSpeed(0.1);
            tank.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            tank.SetDir(DIR_DOWN);
            tank.SetSpeed(0.1);
            tank.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) { NewBullet = true; }
    }
    return NewBullet;
}
bool WorkingWithKeyboardPlayer2(Player &friend_t, MENU page, float CurrentFrame){
    bool FriendBullet = false;
    if (page.TwoPlayers) {
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            friend_t.SetDir(DIR_LEFT);
            friend_t.SetSpeed(0.1);
            friend_t.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            friend_t.SetDir(DIR_RIGHT);
            friend_t.SetSpeed(0.1);
            friend_t.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            friend_t.SetDir(DIR_UP);
            friend_t.SetSpeed(0.1);
            friend_t.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            friend_t.SetDir(DIR_DOWN);
            friend_t.SetSpeed(0.1);
            friend_t.setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) { FriendBullet = true; }
    }
    return FriendBullet;
}


void GlobalDrawing(RenderWindow &window, Map &map, int &enemies_number, Icon &enemy_icon, Player &tank, Icon &lives_icon,
                   Bullet bul[],int n_bul, Game_time &g_time, MENU page, Player &friend_t){
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++) {
            map.CreateMap(map.GetDiagramMap(), i, j);
            window.draw(map.GetMapSprite());//рисуем квадратики на экран
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
    if (page.TwoPlayers) window.draw(friend_t.GetSprite());

}

void GlobalUpdate(Player &tank, Game_time &g_time,Map &map, int &enemy_iterator, Enemy_tank t[], Bullet enemy_bul[],
                  float &time_to_go, int &enemies_number, int &n_enemies, std::mt19937 &engine, MENU page, Player &friend_t) {

    tank.update(g_time.GetTime());
    map.InteractionTankWithMap(map.GetDiagramMap(), tank);

    if (page.TwoPlayers) {
        friend_t.update(g_time.GetTime());
        map.InteractionTankWithMap(map.GetDiagramMap(), friend_t);
    }

    //спауним врагов на поле
    bool sparkle = false;

    time_to_go += g_time.GetTime();
    float sparkle_x = 32;
    float sparkle_y = 32;

    if (time_to_go > 2000 and !sparkle) {
        sparkle = true;

        srand(time(NULL));
        int random = 1 + rand() % 9;
        switch (random) {
            case 1:
            case 4:
            case 7:
                sparkle_x = 32;
                break;
            case 2:
            case 5:
            case 8:
                sparkle_x = 229;
                break;
            case 3:
            case 6:
            case 9:
                sparkle_x = 451;
                break;
        }
//Вот тут надо прописать, чтобы вспышка появлялась в точке (sparkle_x, sparkle_y)
//Передачу в enemy этих координат я уже сделала.
    }

    if (time_to_go > 3000 and enemy_iterator < n_enemies - 1) {
        time_to_go = 0;
        sparkle = false;
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

        Start_Enemy_Function(t[enemy_iterator], 0, 0);
        enemy_iterator++;
    }

        for (int i = 0; i < enemy_iterator; i++) {
            map.InteractionEnemyTankWithMap(map.GetDiagramMap(), t[i]);
        }
    }

bool EnemyUpdateAndDraw(float CurrentFrame, Enemy_tank t[], int &enemy_iterator,Bullet enemy_bul[], std::mt19937 &engine,
                        Map &map, RenderWindow &window,Game_time &g_time, Bullet bul[], int n_bul){
    bool base_is_damaged=false;
    for (int i = 0;i<enemy_iterator;i++) {   //Общий цикл врагов
        //if(t[i].GetIsAlive() && t[i].GetIsOnTheField()){  // Возможно пригодится для добавления новых танков
        for (int j = 0; j < n_bul; j++) {
            if (enemy_bul[i].GetRect().intersects(bul[j].GetRect()) && bul[j].Is_On_f && bul[i].Is_On_f) {
                enemy_bul[i].Is_On_f = false;
                enemy_bul[i].SetSpeed(0);
            }
        }

        for (int j = 0; j < n_bul; j++) {
            if (t[i].GetRect().intersects(bul[j].GetRect()) && bul[j].Is_On_f && t[i].GetIsAlive()) {
                //t[i].SetIsOnTheField(false);
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
            enemy_bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),
                                                                enemy_bul[i]); //Проверяем не попала ли куда-нибудь пуля
            window.draw(enemy_bul[i].sprite); //Рисуем пулю
            t[i].EnemyUpdate(g_time.GetTime(), CurrentFrame);
            if (t[i].GetIsOnTheField()) {  //Если пуля на поле, то устанавливаем ей скорость
                t[i].SetSpeed(t[i].GetSpeed());
            }
            window.draw(t[i].GetSprite());
            // }
        }
    }
    return base_is_damaged;
}

bool OurBullets(Bullet bul[], int &n_bul, int &enemy_iterator, Bullet enemy_bul[],
                Enemy_tank t[], Map &map, Game_time &g_time, RenderWindow &window){

    //пересечение пуль нашего танка
   bool base_is_damaged = false;
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
    return base_is_damaged;
}

void Reset(int STATE, Player &tank,Enemy_tank t[]){
    Map map("Background.png");
    map.SetNumberMap(STATE);
    tank.SetX(164);
    tank.SetY(420);
    int enemies_number = 9;
    for (int i=0;i<enemies_number;i++){
        Start_Enemy_Function(t[i],0,0);
    }
}
void IfTankIsKilled(int enemy_iterator, Bullet enemy_bul[], Player &tank,
                    Game_time g_time, RenderWindow &window, Enemy_tank t[]){
    for (int i = 0;i < enemy_iterator; i++) {
        if (enemy_bul[i].GetRect().intersects(tank.GetRect()) && enemy_bul[i].Is_On_f ) {
            tank.DecreaseLives();
            tank.Respawn();
            tank.SetFlagSpawn(true);
        }
        if (tank.GetRect().intersects(t[i].GetRect()) && t[i].GetIsAlive()){
            tank.SetSpeed(0);
        }
    }
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
}

bool Game(RenderWindow &window, MENU page) {
    ///////--------------------------------

    Map map("Background.png");
    map.SetNumberMap(1);

    ///music
    Audio audio;
    Game_time g_time;
    audio.Init();
    audio.playGame();
    audio.playSpawn();

    int n_bul = 1;
    if (page.TwoPlayers) n_bul = 2;
    Bullet bul[n_bul];
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    bool NewBullet = false;
    bool FriendBullet = false;
    bool base_is_damaged1 = false;
    bool base_is_damaged2 = false ;
    float CurrentFrame = 0;//хранит текущий кадр

    float time_to_go = 0;
    int enemies_number = 9;

    int n_enemies = enemies_number + 2;

    Player tank("sprite.bmp", 3, 5, 26, 26, "main_tank");
    Player friend_t("sprite.bmp", 3, 133, 26, 26, "friend_tank");
    friend_t.Init(324, 420);
    tank.Init(164, 420);

    Enemy_tank t[n_enemies];  //Создаем массив вражеских танков
    Bullet enemy_bul[n_enemies];  //Создаем массив вражеских пуль с расчетом 1 пуля на 1 танк
    int enemy_iterator = 0;

    std::uniform_int_distribution<int> dist(0, 4);

    Icon enemy_icon("sprite.bmp", 48, 273);
    Icon lives_icon("sprite.bmp", 33, 273);

    int STATE=1;

    ///////--------------------------------

    while(1) {
        switch (STATE) {
            case 0: {
                if (!page.end_menu(window)) {
                    return 0;
                }
                STATE = 1;
                Reset(STATE, tank,t);
                break;
            }
            case 1:
            case 2:
            case 3: {

                while (window.isOpen()) {
                    std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count()); //для рандома
                    g_time.Init();

                    Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == Event::Closed) {
                            window.close();
                            return false;
                        }
                    }

                    CurrentFrame += 0.005*g_time.GetTime(); //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
                    if (CurrentFrame > 2) CurrentFrame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.

                    NewBullet = WorkingWithKeyboardPlayer1(tank, page, CurrentFrame);
                    FriendBullet=WorkingWithKeyboardPlayer2(friend_t, page, CurrentFrame);

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

                    time_to_go += g_time.GetTime();
                    base_is_damaged2 = EnemyUpdateAndDraw(CurrentFrame, t, enemy_iterator, enemy_bul, engine, map, window, g_time,bul,n_bul);

                    GlobalUpdate(tank, g_time, map, enemy_iterator, t, enemy_bul, time_to_go, enemies_number, n_enemies, engine, page,  friend_t);


                    base_is_damaged1 = OurBullets(bul,n_bul,enemy_iterator, enemy_bul,t,map,g_time,window);

                    IfTankIsKilled(enemy_iterator, enemy_bul, tank, g_time, window, t);

                    GlobalDrawing(window, map, enemies_number, enemy_icon, tank, lives_icon, bul, n_bul, g_time, page, friend_t);

                    window.display();
                    window.clear();

                    if (!tank.GetIsAlive()||base_is_damaged1||base_is_damaged2) {  //Условия на переход на новый уровень
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
                }
            }
            break;
        }
    }
}
