#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Bullet.h"


using namespace sf;
const int HEIGHT_MAP = 13;//размер карты высота
const int WIDTH_MAP = 14;//размер карты ширина


class Map {
    friend class Player;
private:
    int number_map{};
    Image map_image;
    Sprite map_sprite;
    Texture map_texture;
    //
    String File;
public:
    explicit Map(const String &F);

    void SetNumberMap(int numb_m);

    int GetNumberMap();

    std::vector<String> GetDiagramMap();

    void SetDiagramMap(std::vector<String> Diagram);

    void CreateMap(std::vector<String> Diagram, int i, int j);

    //void Map::ChangeMap(std::vector<String> Diagram, int i, int j,int side)

    Sprite GetMapSprite();

    static void InteractionTankWithMap(std::vector<String> Diagram, Player &tank);

    static bool InteractionBulletWithMap(std::vector<String> Diagram, Bullet &bullet);
};


#endif //GAME_MAP_H
