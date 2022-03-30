#include <chrono>
#include "Game.h"
#include "Map.h"
#include "Audio.h"
#include "Menu.h"
#include "Types.h"

bool WorkingWithKeyboardPlayer1(Player &tank, MENU page, float CurrentFrame, bool base_is_damaged){
    bool NewBullet =false;
    if (tank.GetIsAlive() && (!base_is_damaged)) {
        tank.Control(CurrentFrame);
        if (Keyboard::isKeyPressed(Keyboard::LControl)) {
            NewBullet = true;
        }
    }
    return NewBullet;
}

bool WorkingWithKeyboardPlayer2(Player &friend_t, MENU page, float CurrentFrame, bool base_is_damaged){
    bool FriendBullet = false;
    if (friend_t.GetIsAlive() && (!base_is_damaged)){
        friend_t.Control(CurrentFrame);
        if (Keyboard::isKeyPressed(Keyboard::Space)) { FriendBullet = true;}
    }
    return FriendBullet;
}

void GlobalDrawing(RenderWindow &window, Map &map, int &enemies_number, Icon &enemy_icon, Player &tank, Icon &lives_icon,
                   Bullet bul[],int n_bul, Game_time &g_time, MENU page, Player &friend_t)
                   //int &enemy_iterator,Enemy_tank t[])
                   {

//    map.DrawMapBack(window);

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

}

void GlobalUpdate(Player &tank, Game_time &g_time,Map &map, int &enemy_iterator, Enemy_tank t[], Bullet enemy_bul[],
                  float &time_to_go, int &enemies_number, int &n_enemies, std::mt19937 &engine, MENU page, Player &friend_t) {


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

        Start_Enemy_Function(t[enemy_iterator]);
        enemy_iterator ++;
    }


        for (int i = 0; i < enemy_iterator; i++) {
            map.InteractionEnemyTankWithMap(map.GetDiagramMap(), t[i]);
        }
    }

void DrawIcons(RenderWindow &window, MENU &page, Player &tank, Player &friend_t,
               Icon &lives_icon, Icon &enemy_icon, Icon &friend_lives_icon, int &enemies_number){
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
}

void Bonus(RenderWindow &window, MENU &page, Player &tank, Player &friend_t, Audio &audio,
           Bullet bul[], int &n_bul, int &enemies_number, int &bonus_f, int &randomX, int &randomY, Icon &bonus_icon,
           int &cur_tank_lives, float &tank_speed, int &cur_friend_tank_lives){
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
}

bool EnemyUpdateAndDraw(int &num_alive_enemies, float CurrentFrame, Enemy_tank t[], int &enemy_iterator,Bullet enemy_bul[], std::mt19937 &engine,
                        Map &map, RenderWindow &window,Game_time &g_time, Bullet bul[], int n_bul){
    bool base_is_damaged = false;

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
                num_alive_enemies--;
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
    int enemies_number = 9;
    for (int i=0;i<enemies_number;i++){
        Start_Enemy_Function(t[i]);
    }
    tank.Init(164, 420);
    tank.SetPlayerLives(3);
    tank.SetSpeed(0);

}

void EnemyReset(Map &map, int &enemies_number, Enemy_tank t[], int STATE){
    //Map map("Background.png");
    map.SetNumberMap(STATE);
    for (int i=0;i<enemies_number;i++){
        Start_Enemy_Function(t[i]);
    }
}

void IfTankIsKilled(int enemy_iterator, Bullet enemy_bul[], Player &tank, Player &friend_t,
                    Game_time g_time, RenderWindow &window, Enemy_tank t[], MENU &page){

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
    if (page.TwoPlayers) if (friend_t.GetIsAlive()) window.draw(friend_t.GetSprite());


}

int Game(RenderWindow &window, MENU page, int STATE) {
    ///////--------------------------------

    Map map("Background.png");
    map.SetNumberMap(STATE);

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
    bool base_is_damaged = false;
    bool base_is_damaged1 = false;
    bool base_is_damaged2 = false;
    bool BigFlag = false;
    bool sparkle = false;
    float CurrentFrame = 0;//хранит текущий кадр

    float time_to_go = 0;
    int enemies_number = 9;

    int n_enemies = enemies_number + 2;
    int num_alive_enemies = 10;

    Player tank("sprite.bmp", 3, 5, 26, 26, "main_tank");
    Player friend_t("sprite.bmp", 3, 133, 26, 26, "friend_tank");
    friend_t.Init(290, 420);
    tank.Init(164, 420);
    if (page.TwoPlayers) friend_t.SpawnInit(friend_t.GetX(),friend_t.GetY());
    tank.SpawnInit(tank.GetX(),tank.GetY());

    Enemy_tank t[n_enemies];  //Создаем массив вражеских танков
    Bullet enemy_bul[n_enemies];  //Создаем массив вражеских пуль с расчетом 1 пуля на 1 танк
    int enemy_iterator = 0;

    std::uniform_int_distribution<int> dist(0, 4);

    Icon enemy_icon("sprite.bmp", 48, 273, 16);
    Icon lives_icon("sprite.bmp", 33, 273, 16);
    Icon friend_lives_icon("sprite.bmp", 33, 273, 16);
    Icon bonus_icon("sprite.bmp", 32, 392, 30);

    float tank_speed = 0.1;
    int randomX = 0;
    int randomY = 0;
    int bonus_f = 0;
    int cur_tank_lives = 0;
    int cur_friend_tank_lives = 0;

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

        CurrentFrame += 0.005 * g_time.GetTime(); //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (CurrentFrame > 2)
            CurrentFrame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.


        NewBullet = WorkingWithKeyboardPlayer1(tank, page, CurrentFrame, base_is_damaged);
        if (page.TwoPlayers) FriendBullet = WorkingWithKeyboardPlayer2(friend_t, page, CurrentFrame, base_is_damaged);

        if (NewBullet) {
            if (!bul[0].Is_On_f) {
                bul[0].Is_On_f = true;
                audio.playShoot();
                bul[0].New_Coordinates_and_Dir(tank);
            }
        }

        if (page.TwoPlayers) {
            if (FriendBullet) {
                if (!bul[1].Is_On_f) {
                    bul[1].Is_On_f = true;
                    audio.playShoot();
                    bul[1].New_Coordinates_and_Dir(friend_t);
                }
            }
        }

//        NewBullet = false;
//        FriendBullet = false;

        time_to_go += g_time.GetTime();
        map.DrawMapBack(window);
        GlobalUpdate(tank, g_time, map, enemy_iterator, t, enemy_bul, time_to_go, enemies_number, n_enemies, engine,
                     page, friend_t);

        DrawIcons(window, page, tank, friend_t, lives_icon, enemy_icon, friend_lives_icon, enemies_number);
        Bonus(window, page, tank, friend_t, audio, bul, n_bul, enemies_number, bonus_f, randomX, randomY, bonus_icon, cur_tank_lives, tank_speed, cur_friend_tank_lives);
//        base_is_damaged1 = OurBullets(bul, n_bul, enemy_iterator, enemy_bul, t, map, g_time, window);

        for (int i = 0; i < n_bul; i++) {
            for (int j = 0; j < enemy_iterator; j++) {

                if ( bul[i].Is_On_f && bul[i].GetRect().intersects(enemy_bul[j].GetRect()) && enemy_bul[j].Is_On_f){
                    bul[i].Is_On_f = false;
                    bul[i].SetSpeed(0);
                }

                if (bul[i].Is_On_f && bul[i].GetRect().intersects(t[j].GetRect()) && t[j].GetIsAlive()){
                    t[i].SetIsAlive(false);
                    enemy_bul[i].Is_On_f = false;
                    bul[i].Is_On_f = false;
                    bul[i].SetSpeed(0);
                }

            }
            if (bul[i].GetIsBaseDamaged()){
                base_is_damaged1 = true;
            }
            if (bul[i].Is_On_f) {
                bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),bul[i]);
                bul[i].update(g_time.GetTime());
                window.draw(bul[i].sprite);//рисуем спрайт пули
            }
        }

//        base_is_damaged2 = EnemyUpdateAndDraw(num_alive_enemies, CurrentFrame, t, enemy_iterator, enemy_bul, engine,map, window, g_time, bul, n_bul);
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
                    num_alive_enemies--;
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
                    base_is_damaged2 = true;
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

        IfTankIsKilled(enemy_iterator, enemy_bul, tank, friend_t, g_time, window, t, page);
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
        GlobalDrawing(window, map, enemies_number, enemy_icon, tank, lives_icon, bul, n_bul, g_time, page, friend_t);

        map.DrawMapForward(window);
        window.display();
        window.clear();

        if (!tank.GetIsAlive() || base_is_damaged1 || base_is_damaged2) {  //Условия на переход на новый уровень
            return 0;
        }
        if (num_alive_enemies == 0) {
            if(STATE<3){
                return ++STATE;
            } else return 4;

        }
    }
}
