//
// Created by Huawei on 08.02.2022.
//
#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <SFML/Graphics.hpp>

const int HEIGHT_MAP = 13;
const int WIDTH_MAP = 14;

sf::String TileMap[HEIGHT_MAP] = {
        "FFFFFFFFFFFFF@",
        "F4F4F4F4F4F4F@",
        "F4F4F4F4F4F4F@",
        "F4F4F494F4F4F@",
        "F4F4F3F3F4F4F@",
        "F3F3F1F1F3F3F@",
        "1F11F3F3F11F1@",
        "8F33F1F1F33F8@",
        "F1F1F444F1F1F@",
        "F4F4F4F4F4F4F@",
        "F4F4F3F3F4F4F@",
        "F4F4F?1?F4F4F@",
        "FFFFF0F2FFFFF@",
};

#endif //GAME_MAP_H
