#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
public:
    Player(const String F, int X, int Y, int W, int H) {
        File = F;
        m_start_x = X;
        m_start_y = Y;
        m_width = W;
        m_height = H;
        m_image.loadFromFile("..\\images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
        //m_image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
        m_texture.loadFromImage(m_image);//закидываем наше изображение в текстуру
        m_sprite.setTexture(m_texture);//заливаем спрайт текстурой
        m_sprite.setTextureRect(IntRect(3, 5, m_width, m_height));
        m_sprite.setPosition(m_start_x,m_start_y);

    }
    void Init(int x, int y);
    void Draw(Texture& General_Texture, float left, float top, float width, float height);

    double GetSpeed();
    int GetX();
    int GetY();
    int GetSpeedX();
    int GetSpeedY();
    void SetSpeed(double speed);
    void SetX(int x);
    void SetY(int y);
    void SetSpeedX(int vx);
    void SetSpeedY(int vy);
    Sprite GetSprite();

private:
    int m_width;
    int m_height;
    Image m_image;
    Sprite m_sprite;
    Texture m_texture;
    float m_start_x;       //стартовая позиция
    float m_start_y;       //
    String File;
    double m_speed;         //базовая скорость
    double m_x, m_y;        //позиция игрока
    double m_vx, m_vy;      //скорость игрока (ускорение по x и y)
    double m_speed_ratio;   //коэффициент скорости
    double m_bullet_speed;  //скорость пули
    int m_bullet_power;     //сила пули

    int m_lifes; //кол-во жизней

    int  m_tank_width; //высота и ширина в пикселях
    int m_tank_height;


};

#endif