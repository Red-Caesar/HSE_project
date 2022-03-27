#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "Audio.h"
using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
//class Bullet {// класс Игрока
//public:
//    float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
//    int dir = 0; //направление (direction) движения игрока
//    String File; //файл с расширением
//    Image image;//сфмл изображение
//    Texture texture;//сфмл текстура
//    Sprite sprite;//сфмл спрайт
//    bool Is_On_f = false;
//
//
//    Bullet () {
//        //File = F;//имя файла+расширение
//        w = 7.0;
//        h = 7.0;//высота и ширина
//        //image.loadFromFile("..\\images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
//        //image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
//        //texture.loadFromImage(image);//закидываем наше изображение в текстуру
//        //sprite.setTexture(texture);//заливаем спрайт текстурой
//        x = 0;
//        y = 0;//координата появления спрайта
//        dir = 0;
//        speed = 0.1;
//        sprite.setTextureRect(IntRect(156, 27, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
//    }
//
//
//    Bullet (Player &player, String F){  //Конструктор с параметрами(формальными) для класса Bullet. При создании объекта класса мы будем задавать имя файла, координату Х и У, направление
//        File = F;//имя файла+расширение
//        //SetWidth(7.0);
//        w = 7.0;
//        h = 7.0;//высота и ширина
//        image.loadFromFile("..\\images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
//        //image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
//        texture.loadFromImage(image);//закидываем наше изображение в текстуру
//        sprite.setTexture(texture);//заливаем спрайт текстурой
//        x = player.GetX();
//        y = player.GetY();//координата появления спрайта
//        dir = player.GetDir();
//        speed = 0.1;
//        sprite.setTextureRect(IntRect(156, 27, w,h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
//    }
//
//
//    void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
//    {
//        switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
//        {
//            case 0:
//                dx = speed;
//                dy = 0;
//                break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
//            case 1:
//                dx = -speed;
//                dy = 0;
//                break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
//            case 2:
//                dx = 0;
//                dy = speed;
//                break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
//            case 3:
//                dx = 0;
//                dy = -speed;
//                break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
//        }
//
//
//
//        x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
//        y += dy * time;//аналогично по игреку
//
//        if(x>=32*14||y>=32*13||x<=0||y<=0){
//            speed = 0;
//            Is_On_f = false;
//        }
//        else{
//            sprite.setPosition(x, y);
//        }
//        //speed = 0;//зануляем скорость, чтобы персонаж остановился.
//        //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
//    }
//
//    void New_Coordinates_and_Dir(Player &player){
//        dir = player.GetDir();
//        x = player.GetX() + 10;
//        y = player.GetY() + 10;
//        speed = 0.1;
//    }
//
//    void SetFile(String F){
//        File = F;
//        image.loadFromFile("..\\images/" + File);
//        texture.loadFromImage(image);
//        sprite.setTexture(texture);
//    }
//};

int main() {

    RenderWindow window(VideoMode(544, 480), "Tan4iki!");
    Map map("Background.png");
    map.SetNumberMap(1);
    Player tank("sprite.bmp", 32, 32, 26, 26);
    ///music

    Audio audio;
    audio.Init();
    audio.playGame();

    int Dir = 0;

    bool NewBullet = false;
    bool BigFlag = false;
    float CurrentFrame = 0;//хранит текущий кадр

    Clock clock;



    int n_bul = 1;
    Bullet bul[n_bul];
    for (int i = 0; i < n_bul; i++) {
        bul[i].SetFile("heart.bmp");
    }

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        // Обрабатываем очередь событий в цикле
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();}

        if (Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))) { tank.SetDir(1); tank.SetSpeed(0.1); tank.setRect();}
        if (Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))) { tank.SetDir(0);tank.SetSpeed(0.1);tank.setRect();}
        if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))) { tank.SetDir(3); tank.SetSpeed(0.1); tank.setRect(); }
        if (Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))) { tank.SetDir(2); tank.SetSpeed(0.1); tank.setRect();}
        if ((Keyboard::isKeyPressed(Keyboard::Space))) { NewBullet = true; }
        ///////////////////////////////////////////

        if (NewBullet) {
            for (int i = 0; i < n_bul; i++) {  // Добавление новой пули
                if (!bul[i].Is_On_f) {
                    bul[i].Is_On_f = true;
                    audio.playShoot();
                    bul[i].New_Coordinates_and_Dir(tank);
                    break;
                }
            }
            NewBullet = false;
        }

        tank.update(time);
        map.InteractionTankWithMap(map.GetDiagramMap(), tank);
        window.clear();

/////////////////////////////Рисуем карту/////////////////////
        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++) {
                map.CreateMap(map.GetDiagramMap(), i, j);
                window.draw(map.GetMapSprite());//рисуем квадратики на экран
            }
       // window.draw(map.GetMapSprite());
        for (int i = 0; i < n_bul; i++) {
            if (bul[i].Is_On_f) {
                bul[i].update(time);
                bul[i].Is_On_f = map.InteractionBulletWithMap(map.GetDiagramMap(),bul[i]);
                window.draw(bul[i].sprite);//рисуем спрайт пули
            }
        }
        window.draw(tank.GetSprite());
        window.display();
    }
    return 0;
}