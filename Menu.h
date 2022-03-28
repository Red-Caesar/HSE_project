#ifndef GAME_MENU_H
#define GAME_MENU_H
#include <SFML/Graphics.hpp>
using namespace sf;
bool menu (RenderWindow &window);
class Icon {
public:
    float x, y, w, h, a, b = 0;
    String File;
    Image image;
    Texture icon_texture;
    Sprite icon_sprite;

    Icon(String F, float X, float Y) {
        File = F;
        x = X;
        y = Y;
        // x = 48/33;
        //y = 273;
        w = 16;
        h = 16;
        image.loadFromFile("..\\images/" + File);
        icon_texture.loadFromImage(image);
        icon_sprite.setTexture(icon_texture);
        icon_sprite.setTextureRect(IntRect(x, y, w,h));
    }
    void CreateIcon(int x, int y) {
        // x = 464;
        // y = 64/200;
        icon_sprite.setPosition(x, y);
    }
};
#endif //GAME_MENU_H
