#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace sf;

int main()
{
	// Объект, который, собственно, является главным окном приложения
    //Можно в параметрах прописать потом Style::fullscreen
	RenderWindow window(VideoMode(448, 416), "Tan4iki!");
//    Image main_tank_image;
//    main_tank_image.loadFromFile("sprites/main_tank_forward.png");

//    Texture main_tank_texture;
//    main_tank_texture.loadFromFile("images/main_tank_forward.png");
    Texture General_Texture;
    General_Texture.loadFromFile("..\\images/sprite.bmp");

    Sprite main_tank_sprite;
    main_tank_sprite.setTexture(General_Texture);
    main_tank_sprite.setTextureRect(IntRect(3,5,26,26));
//    Если поставить в rectHeight минус, то танк поедет назад
    main_tank_sprite.setPosition(13,14);

    Image map_image;
    map_image.loadFromFile("..\\images/Background.png");//загружаем файл для карты
    Texture Map_Texture;//текстура карты
    Map_Texture.loadFromImage(map_image);

//    Texture Map_Texture;
//    Map_Texture.loadFromFile("..\\images/Background.png");
    Sprite map_sprite;//создаём спрайт для карты
    map_sprite.setTexture(Map_Texture);//заливаем текстуру спрайтом


    // Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed) {
                window.close(); // тогда закрываем его
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) { main_tank_sprite.move(-5, 0); main_tank_sprite.setTextureRect(IntRect(5,99,26,26));} //первая координата Х отрицательна =>идём влево
            if (Keyboard::isKeyPressed(Keyboard::Right)) { main_tank_sprite.move(5, 0); main_tank_sprite.setTextureRect(IntRect(1,35,26,26));} //первая координата Х положительна =>идём вправо
            if (Keyboard::isKeyPressed(Keyboard::Up)) { main_tank_sprite.move(0, -5); main_tank_sprite.setTextureRect(IntRect(3,5,26,26));} //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
            if (Keyboard::isKeyPressed(Keyboard::Down)) { main_tank_sprite.move(0, 5); main_tank_sprite.setTextureRect(IntRect(3,65,26,26));} //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)

        }
        window.clear();
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
//                map_sprite.setTextureRect(IntRect(160,0,32,32))
                if (TileMap[i][j] == 'F') continue;
                if (TileMap[i][j] == '0')  map_sprite.setTextureRect(IntRect(0,64,32,32));
                if (TileMap[i][j] == '1')  map_sprite.setTextureRect(IntRect(0,128,32,32));
                if (TileMap[i][j] == '2')  map_sprite.setTextureRect(IntRect(0,32,32,32));
                if (TileMap[i][j] == '3')  map_sprite.setTextureRect(IntRect(0,96,32,32));
                if (TileMap[i][j] == '4')  map_sprite.setTextureRect(IntRect(0,0,32,32));
                if (TileMap[i][j] == '8')  map_sprite.setTextureRect(IntRect(64,96,32,32));
                if (TileMap[i][j] == '@') continue;
                if (TileMap[i][j] == '?') continue;
                map_sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                window.draw(map_sprite);//рисуем квадратики на экран
            }
        window.draw(main_tank_sprite);

	// Отрисовка окна
	window.display();
	}

	return 0;
}