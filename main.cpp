#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
using namespace sf;

int main() {
    // Объект, который, собственно, является главным окном приложения
    //Можно в параметрах прописать потом Style::fullscreen
    RenderWindow window(VideoMode(338, 364), "Tan4iki!");

    Clock clock;
    Map map("Background.png");

    map.SetNumberMap(0);
    Player tank( "sprite.bmp", 20, 20, 26, 26);

    // Главный цикл приложения. Выполняется, пока открыто окно
    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        // Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event)) {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                window.close(); // тогда закрываем его
            }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
                tank.SetDir(1); tank.SetSpeed(0.1);
                tank.setRect();

            } //первая координата Х отрицательна =>идём влево

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
                tank.SetDir(0); tank.SetSpeed(0.1);
                tank.setRect();
            } //первая координата Х положительна =>идём вправо

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
                tank.SetDir(3); tank.SetSpeed(0.1);
                tank.setRect();
            } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
                tank.SetDir(2); tank.SetSpeed(0.1);
                tank.setRect();
            } //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)

        tank.update(time);
       // map.InteractionWithMap(map.GetDiagramMap(),tank);
        window.clear();


/////////////////////////////Рисуем карту/////////////////////
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
               map.CreateMap(map.GetDiagramMap(),i,j);
               window.draw(map.GetMapSprite());//рисуем квадратики на экран
            }
        window.draw(map.GetMapSprite());
        window.draw(tank.GetSprite());
        // Отрисовка окна
        window.display();
    }

    return 0;
}