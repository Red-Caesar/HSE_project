#include "Menu.h"
bool menu (RenderWindow &window){
    Texture menuTexture1, menuTexture2, menuTexture3;
    Sprite menuSprite1, menuSprite2, menuSprite3;
    Image menuImage1,menuImage2,menuImage3;

    menuImage1.loadFromFile("..\\images/sprite.bmp");
    menuImage2.loadFromFile("..\\images/sprite.bmp");
    menuImage3.loadFromFile("..\\images/sprite.bmp");

    menuTexture1.loadFromImage(menuImage1);
    menuTexture2.loadFromImage(menuImage2);
    menuTexture3.loadFromImage(menuImage3);

    menuSprite1.setTexture(menuTexture1);
    menuSprite1.setTextureRect(IntRect(135, 274, 374, 137));
    menuSprite1.setPosition(75,50);
    menuSprite2.setTexture(menuTexture2);
    menuSprite2.setTextureRect(IntRect(354, 423, 62, 14));
    menuSprite2.setPosition(193,230);
    menuSprite3.setTexture(menuTexture3);
    menuSprite3.setTextureRect(IntRect(1, 35, 26,26));
    menuSprite3.setPosition(165,226);

    bool IsMenu = true;
    bool IsPlay=false;

    while(IsMenu){
        IsPlay=false;

        if(IntRect(193,230,62, 14).contains(Mouse::getPosition(window))){
            window.draw(menuSprite3);
            IsPlay=true;
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (IsPlay) {
                IsMenu = false;
            }
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return false;}
        }

        window.draw(menuSprite1);
        window.draw(menuSprite2);

        window.display();
        window.clear();
    }
    return true;
}

