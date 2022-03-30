#include <windows.h>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"

using namespace sf;


int main() {

    RenderWindow window(VideoMode(544, 480), "Tan4iki!");
    MENU page;
    if(!page.menu(window)){
        return 0;
    }
    if(!Game(window, page)){
        return 0;
    }
        window.display();
    return 0;
}