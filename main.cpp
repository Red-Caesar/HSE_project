#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Bullet {// класс Игрока
public:
    float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0; //направление (direction) движения игрока
    String File; //файл с расширением
    Image image;//сфмл изображение
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт
    bool Is_On_f = false;


    Bullet () {
        //File = F;//имя файла+расширение
        w = 7.0;
        h = 7.0;//высота и ширина
        //image.loadFromFile("..\\images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
        //image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
        //texture.loadFromImage(image);//закидываем наше изображение в текстуру
        //sprite.setTexture(texture);//заливаем спрайт текстурой
        x = 0;
        y = 0;//координата появления спрайта
        dir = 0;
        speed = 0.1;
        sprite.setTextureRect(IntRect(156, 27, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
    }


    Bullet (Player &player, String F){  //Конструктор с параметрами(формальными) для класса Bullet. При создании объекта класса мы будем задавать имя файла, координату Х и У, направление
        File = F;//имя файла+расширение
        //SetWidth(7.0);
        w = 7.0;
        h = 7.0;//высота и ширина
        image.loadFromFile("..\\images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
        //image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
        texture.loadFromImage(image);//закидываем наше изображение в текстуру
        sprite.setTexture(texture);//заливаем спрайт текстурой
        x = player.GetX();
        y = player.GetY();//координата появления спрайта
        dir = player.GetDir();
        speed = 0.1;
        sprite.setTextureRect(IntRect(156, 27, w,h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
    }


    void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
    {
        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
            case 0:
                dx = speed;
                dy = 0;
                break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
            case 1:
                dx = -speed;
                dy = 0;
                break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
            case 2:
                dx = 0;
                dy = speed;
                break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
            case 3:
                dx = 0;
                dy = -speed;
                break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        }



        x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        y += dy * time;//аналогично по игреку

        if(x>=32*14||y>=32*13||x<=0||y<=0){
            speed = 0;
            Is_On_f = false;
        }
        else{
            sprite.setPosition(x, y);
        }
        //speed = 0;//зануляем скорость, чтобы персонаж остановился.
        //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }

    void New_Coordinates_and_Dir(Player &player){
        dir = player.GetDir();
        x = player.GetX();
        y = player.GetY();
        speed = 0.1;
    }

    void SetFile(String F){
        File = F;
        image.loadFromFile("..\\images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
};


int main()
{

    int Dir = 0;
    RenderWindow window(sf::VideoMode(640, 480), "Bullet");
    bool NewBullet = false;
    bool BigFlag = false;
    float CurrentFrame = 0;//хранит текущий кадр
    Clock clock;

    Player main_tank( "sprite.bmp", 20, 20, 26, 26);
    //Bullet b(main_tank,"heart.bmp");//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
    int n_bul=20;
    Bullet bul[n_bul];
    for(int i=0;i<n_bul;i++){
        bul[i].SetFile("heart.bmp");
    }


    // X Y надо передавать из положения танка
    // направление тоже

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        //Но пока надо чтобы при нажатии нужной стрелки появлялась пуля и летела в нужном направлении.
        // НЕ нужны кейсы тру-фолс в новой_пуле, чтобы обрабатывать следующие нажатия
        // (в тру) просто надо как-то обрабатывать направление в свитче. Тру-фолс только на то,
        // есть пуля в кадре или нет, надо ее рисовать или нет


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////

            if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
                Dir = 1; // b.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
            }

            if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
                Dir = 0; // b.speed = 0.1;//направление вправо, см выше
            }

            if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
                Dir = 3; // b.speed = 0.1;//направление вниз, см выше

            }

            if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
                Dir = 2; //b.speed = 0.1;//направление вверх, см выше

            }
            if ((Keyboard::isKeyPressed(Keyboard::Space))){
                NewBullet = true;
            }

            ////////////////////////////////////////////
            if (event.type == Event::KeyPressed)//событие нажатия клавиши
                if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down) || (event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right)) {
                    main_tank.SetDir(Dir);
                    main_tank.SetSpeed(1.5);
                    main_tank.setRect();
                }
        }

        ///////////////////////////////////////////


        if (NewBullet) {
            for(int i=0 ; i < n_bul; i++){                               // Добавление новой пули
                if(!bul[i].Is_On_f){
                    bul[i].Is_On_f = true;
                    bul[i].New_Coordinates_and_Dir(main_tank);
                    break;
                }
            }
            NewBullet = false;
        }
        main_tank.update(time);
        window.clear();
        window.draw(main_tank.GetSprite());

        for(int i=0; i < n_bul; i++){
            if(bul[i].Is_On_f){
                bul[i].update(time);
                window.draw(bul[i].sprite);//рисуем спрайт пули
            }
        }
        window.display();
    }
    return 0;
}