#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

int main() {
    // Объект, который, собственно, является главным окном приложения
    //Можно в параметрах прописать потом Style::fullscreen
    RenderWindow window(VideoMode(338, 364), "Tan4iki!");
//    Image main_tank_image;
//    main_tank_image.loadFromFile("sprites/main_tank_forward.png");

//    Texture main_tank_texture;
//    main_tank_texture.loadFromFile("images/main_tank_forward.png");
    //Texture General_Texture;
   // General_Texture.loadFromFile("..\\images/m_sprite.bmp");
    Player tank( "sprite.bmp", 13, 14, 26, 26);
    //tank.Init(13, 14);
    //tank.Draw(General_Texture, 3, 5, 26, 26);
//    tank.m_sprite.setTexture(General_Texture);
//    tank.m_sprite.setTextureRect(IntRect(3, 5, 26, 26));
    // Главный цикл приложения. Выполняется, пока открыто окно
    while (window.isOpen()) {
        // Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event)) {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed) {
                window.close(); // тогда закрываем его
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                tank.GetSprite().move(-5, 0);
                tank.GetSprite().setTextureRect(IntRect(5, 99, 26, 26));
            } //первая координата Х отрицательна =>идём влево
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                tank.GetSprite().move(5, 0);
                tank.GetSprite().setTextureRect(IntRect(1, 35, 26, 26));
            } //первая координата Х положительна =>идём вправо
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                tank.GetSprite().move(0, -5);
                tank.GetSprite().setTextureRect(IntRect(3, 5, 26, 26));
            } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                tank.GetSprite().move(0, 5);
                tank.GetSprite().setTextureRect(IntRect(3, 65, 26, 26));
            } //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)

        }
        window.clear();
        window.draw(tank.GetSprite());
        // Отрисовка окна
        window.display();
    }

    return 0;
}