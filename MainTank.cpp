//
// Created by 79101 on 08.02.2022.
//

#include "MainTank.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

void MainTank::Init(Sprite &object ,int x, int y) {
    object.setPosition(x,y);
    m_speed = 5.5;

    //m_can_shoot = true;
    //m_bullets_in_game = 0;

    //m_start_x = x;  m_start_y = y;

    //SetPlayerLevel(0);
}


void MainTank::Draw(Sprite object, int left, int top, int width, int height){
    Texture General_Texture;
    General_Texture.loadFromFile("..\\images/sprite.bmp");

    object.setTexture(General_Texture);
    object.setTextureRect(IntRect(left, top, width, height));
//    Если поставить в rectHeight минус, то танк поедет назад

}