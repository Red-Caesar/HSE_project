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
    menuSprite2.setPosition(230,230);
    menuSprite3.setTexture(menuTexture3);
    menuSprite3.setTextureRect(IntRect(1, 35, 26,26));
    menuSprite3.setPosition(202,226);

    bool IsMenu = true;
    bool IsPlay=false;

    while(IsMenu){
        IsPlay=false;

        if(IntRect(230,230,62, 14).contains(Mouse::getPosition(window))){
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

bool end_menu (RenderWindow &window){
    Texture endTexture1, endTexture2, endTexture3;
    Sprite endSprite1, endSprite2, endSprite3;
    Image endImage1,endImage2,endImage3;

    endImage1.loadFromFile("..\\images/game-over.bmp");
    endImage2.loadFromFile("..\\images/game_over.bmp");
    endImage3.loadFromFile("..\\images/sprite.bmp");

    endTexture1.loadFromImage(endImage1);
    endTexture2.loadFromImage(endImage2);
    endTexture3.loadFromImage(endImage3);

    endSprite1.setTexture(endTexture1);
    endSprite1.setTextureRect(IntRect(194, 144, 493-194, 279-144));
    endSprite1.setPosition(115,95);
    endSprite2.setTexture(endTexture2);
    endSprite2.setTextureRect(IntRect(307, 406, 131, 11));
    endSprite2.setPosition(200,275);
    endSprite3.setTexture(endTexture3);
    endSprite3.setTextureRect(IntRect(1, 35, 26,26));
    endSprite3.setPosition(170,267);

    bool IsMenu = true;
    bool IsPlay=false;

    while(IsMenu){
        IsPlay=false;

        if(IntRect(200,275,131, 11).contains(Mouse::getPosition(window))){
            window.draw(endSprite3);
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

        window.draw(endSprite1);
        window.draw(endSprite2);

        window.display();
        window.clear();
    }
    return true;
}
