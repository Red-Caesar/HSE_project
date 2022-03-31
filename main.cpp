#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "Types.h"

using namespace sf;


int main() {
    RenderWindow window(VideoMode(544, 480), "Tan4iki!");
    MENU page;
    if (!page.menu(window)) {
        return 0;
    }
    int STATE = 1;
    while (1) {
        switch (STATE) {
            case 0:
                if (!page.end_menu(window)) {
                    return 0;
                }
                STATE = 1;
                break;
            case 1:
            case 2:
            case 3:
                STATE = StartGame(STATE, window, page);
                break;
            case 4:
                if (!page.win(window)) {
                    return 0;
                }
                break;

        }
    }

    return 0;
}