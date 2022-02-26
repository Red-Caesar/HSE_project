#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
using namespace sf;
const int HEIGHT_MAP = 12;//размер карты высота
const int WIDTH_MAP = 12;//размер карты ширина


class Map {
private:
    int number_map{};
    Image map_image;
    Sprite map_sprite;
    Texture map_texture;
    //
    String File;
public:
    Map(const String& F);

    void SetNumberMap(int numb_m);
    int GetNumberMap();
    std::vector<String> GetDiagramMap();
    void CreateMap(std::vector<String> Diagram,int i,int j);
    Sprite GetMapSprite();
    static void InteractionWithMap(std::vector<String> Diagram,Player tank);


};


#endif //GAME_MAP_H
