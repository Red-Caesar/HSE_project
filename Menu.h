#ifndef GAME_MENU_H
#define GAME_MENU_H
#include <SFML/Graphics.hpp>
using namespace sf;

class MENU{
public:
    bool TwoPlayers = false;
    bool menu (RenderWindow &window);
    bool end_menu (RenderWindow &window);
    bool win (RenderWindow &window);
    void NewStage(int STATE, RenderWindow &window);
};


class Icon {
public:
    float x, y, w, h, a, b = 0;
    String File;
    Image image;
    Texture icon_texture;
    Sprite icon_sprite;

    Icon(String F, float X, float Y, int S) {
        File = F;
        x = X;
        y = Y;
        w = S;
        h = S;
        image.loadFromFile("..\\images/" + File);
        icon_texture.loadFromImage(image);
        icon_sprite.setTexture(icon_texture);
        icon_sprite.setTextureRect(IntRect(x, y, w,h));
    }
    void CreateIcon(int x, int y) {
        icon_sprite.setPosition(x, y);
    }

};
#endif //GAME_MENU_H
