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
    int STATE=1;
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
                STATE = Game(window, page, STATE);
                break;
            case 4:
                if (!page.win(window)) {
                    return 0;
                }
                break;
            case 5:
                return 0;
        }
    }
}