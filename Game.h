
#ifndef GAME_GAME_H
#define GAME_GAME_H
#include <chrono>
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Audio.h"
#include "Game_time.h"
#include "Enemy_tanks.h"
#include "Menu.h"
#include "Types.h"

void EnemiesAppear(int &enemy_iterator, Enemy_tank t[], Bullet enemy_bul[],
                   float &time_to_go, int &enemies_number, int &n_enemies, std::mt19937 &engine);

void DrawIcons(RenderWindow &window, MENU &page, Player &tank, Player &friend_t,
               Icon &lives_icon, Icon &enemy_icon, Icon &friend_lives_icon, int &enemies_number);

void Bonus(RenderWindow &window, MENU &page, Player &tank, Player &friend_t, Audio &audio,
           Bullet bul[], int &n_bul, int &enemies_number, int &bonus_f, int &randomX, int &randomY, Icon &bonus_icon,
           int &cur_tank_lives, float &tank_speed, int &cur_friend_tank_lives);

void OurBullets(Bullet bul[], int &n_bul, int &enemy_iterator, Bullet enemy_bul[],
                Enemy_tank t[], Map &map, Game_time &g_time, RenderWindow &window, bool &base_is_damaged);

void EnemyUpdateAndDraw(int &num_alive_enemies, float CurrentFrame, Enemy_tank t[], int &enemy_iterator,Bullet enemy_bul[], std::mt19937 &engine,
                        Map &map, RenderWindow &window,Game_time &g_time, Bullet bul[], int n_bul, bool &base_is_damaged);

void IfTankIsKilled(int enemy_iterator, Bullet enemy_bul[], Player &tank, Player &friend_t,
                    Game_time g_time, RenderWindow &window, Enemy_tank t[], MENU &page);

int StartGame(int &level, RenderWindow &window, MENU &page);
#endif //GAME_GAME_H  */
