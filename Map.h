#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Bullet.h"


using namespace sf;
const int HEIGHT_MAP = 15;//размер карты высота
const int WIDTH_MAP = 17;//размер карты ширина


class Map {
    friend class Player;
private:
    int number_map{};
    Image map_image;
    Sprite map_sprite;
    Texture map_texture;
    //
    String File;
    std::vector<String> ZeroMap = {
            "0000000000",
            "0         0",
            "0   s     0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "00000000000",
    };
    std::vector<String> FirstMap = {
            "@@@@@@@@@@@@@@@@@",
            "@FFFFFFFFFFFFF@@@",
            "@FFF4F4F4F4F4F@@@",
            "@FFF4F4F4F4F4F@@@",
            "@FFF4F444F4F4F@@@",
            "@FFF4F3F3F4F4F@@@",
            "@F3F3F1F1F3F3F@@@",
            "@1F11F3F3F11F1@@@",
            "@8F33F1F1F33F8@@@",
            "@F1F1F444F1F1F@@@",
            "@F4F4F4F4F4F4F@@@",
            "@F4F4F3F3F4F4F@@@",
            "@F4F4F?1?F4F4F@@@",
            "@FFFFF0F2FFFFF@@@",
            "@@@@@@@@@@@@@@@@@",
    };
    std::vector<String> TileMap = {
            "FFFFFFFFFFFFF@",
            "FFFFFFF4F4F4F@",
            "FFF4FFF4F4F4F@",
            "FFFFFF94F4F4F@",
            "FFFFFFF3F4F4F@",
            "F3FFF1F1F3F3F@",
            "1FF4F3F3F11F1@",
            "8FFFF1F1F33F8@",
            "F1FFF444F1F1F@",
            "F4F4F4F4F4F4F@",
            "F4F4F3F3F4F4F@",
            "F4F4F?1?F4F4F@",
            "FFFFF0F2FFFFF@",
    };
public:
    explicit Map(const String &F);

    void SetNumberMap(int numb_m);

    Sprite GetMapSprite();

    int GetNumberMap();

    std::vector<String> GetDiagramMap();

    void SetDiagramMap(int i, int j, char texture);

    void CreateMap( std::vector<String> Diagram, int i, int j);

    static void InteractionTankWithMap(std::vector<String> Diagram, Player &tank);

    bool InteractionBulletWithMap(std::vector<String> Diagram, Bullet &bullet);


};


#endif //GAME_MAP_H
