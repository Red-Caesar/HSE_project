#include <iostream>
#include <SFML/Graphics.hpp>
#include "MainTank.h"
using namespace sf;

int main() {
    // Объект, который, собственно, является главным окном приложения
    //Можно в параметрах прописать потом Style::fullscreen
    RenderWindow window(VideoMode(338, 364), "Tan4iki!");


//    Если поставить в rectHeight минус, то танк поедет назад
    MainTank::Init(MainTank::main_tank_sprite,13, 14);
    MainTank::Draw(MainTank::main_tank_sprite,3, 5, 26, 26);
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
                MainTank::main_tank_sprite.move(-5, 0);
                MainTank::main_tank_sprite.setTextureRect(IntRect(5, 99, 26, 26));
            } //первая координата Х отрицательна =>идём влево
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                MainTank::main_tank_sprite.move(5, 0);
                MainTank::main_tank_sprite.setTextureRect(IntRect(1, 35, 26, 26));
            } //первая координата Х положительна =>идём вправо
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                MainTank::main_tank_sprite.move(0, -5);
                MainTank::main_tank_sprite.setTextureRect(IntRect(3, 5, 26, 26));
            } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                MainTank::main_tank_sprite.move(0, 5);
                MainTank::main_tank_sprite.setTextureRect(IntRect(3, 65, 26, 26));
            } //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)

        }
        window.clear();
        window.draw( MainTank::main_tank_sprite);
        // Отрисовка окна
        window.display();
    }

    return 0;
}