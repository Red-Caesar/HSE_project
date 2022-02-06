#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
class Tank{
public:
    float speed;
    float hp;
private:
    void fire();
    void Collision();
};
int main()
{
	// Объект, который, собственно, является главным окном приложения
    //Можно в параметрах прописать потом Style::fullscreen
	RenderWindow window(VideoMode(640, 480), "Tan4iki!");
//    Image main_tank_image;
//    main_tank_image.loadFromFile("sprites/main_tank_forward.png");

//    Texture main_tank_texture;
//    main_tank_texture.loadFromFile("images/main_tank_forward.png");
    Texture General_Texture;
    General_Texture.loadFromFile("images/General-Sprites.png");

    Sprite main_tank_sprite;
    main_tank_sprite.setTexture(General_Texture);
    main_tank_sprite.setTextureRect(IntRect(0,0,15,16));
//    Если поставить в rectHeight минус, то танк поедет назад
    main_tank_sprite.setPosition(13,14);
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
            if (Keyboard::isKeyPressed(Keyboard::Left)) { main_tank_sprite.move(-5, 0); main_tank_sprite.setTextureRect(IntRect(47,0,16,15));} //первая координата Х отрицательна =>идём влево
            if (Keyboard::isKeyPressed(Keyboard::Right)) { main_tank_sprite.move(5, 0); main_tank_sprite.setTextureRect(IntRect(47,0,-16,15));} //первая координата Х положительна =>идём вправо
            if (Keyboard::isKeyPressed(Keyboard::Up)) { main_tank_sprite.move(0, -5); main_tank_sprite.setTextureRect(IntRect(0,0,15,16));} //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
            if (Keyboard::isKeyPressed(Keyboard::Down)) { main_tank_sprite.move(0, 5); main_tank_sprite.setTextureRect(IntRect(80,0,15,16));} //вторая координата (У) положительна =>идём вниз (если не понятно почему именно вниз - смотрим предыдущие уроки)

        }
        window.clear();
        window.draw(main_tank_sprite);
	// Отрисовка окна
	window.display();
	}

	return 0;
}