//
// Created by NP on 23.03.2022.
//

#include "Bullet.h"

Bullet::Bullet() {
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
    sprite.setTextureRect(IntRect(156, 27, w,h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов


}

void Bullet::update(float time) {
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
    x += dx *
         time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
    y += dy * time;//аналогично по игреку

    if (x >= 32 * 16 || y >= 32 * 15 || x <= 32 || y <= 32) {
        speed = 0;
        Is_On_f = false;
    } else {
        sprite.setPosition(x, y);
    }
    //speed = 0;//зануляем скорость, чтобы персонаж остановился.
    //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.

}

void Bullet::New_Coordinates_and_Dir(Player &player) {
    dir = player.GetDir();
    x = player.GetX() + 10;
    y = player.GetY() + 10;
    speed = 0.1;
}

void Bullet::SetFile(String F) {
    File = F;
    image.loadFromFile("..\\images/" + File);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

}

float Bullet::GetX() const {
    return x;
}

float Bullet::GetY() const {
    return y;
}

float Bullet::GetSpeedX() const {
    return dx;
}

float Bullet::GetSpeedY() const {
    return dy;
}


void Bullet::SetX(int cur_x) {
    x = cur_x;
}

void Bullet::SetY(int cur_y) {
    y = cur_y;
}

float Bullet::GetH() const {
    return h;
}

float Bullet::GetW() const {
    return w;
}

//Bullet::Bullet(Player &player, String F) {
//    File = F;//имя файла+расширение
//    //SetWidth(7.0);
//    w = 7.0;
//    h = 7.0;//высота и ширина
//    image.loadFromFile("..\\images/" +
//                       File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
//    //image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
//    texture.loadFromImage(image);//закидываем наше изображение в текстуру
//    sprite.setTexture(texture);//заливаем спрайт текстурой
//    x = player.GetX();
//    y = player.GetY();//координата появления спрайта
//    dir = player.GetDir();
//    speed = 0.1;
//    sprite.setTextureRect(IntRect(156, 27, w,
//                                  h));
//
//}
