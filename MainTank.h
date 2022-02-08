//
// Created by 79101 on 08.02.2022.
//

#ifndef GAME_MAINTANK_H
#define GAME_MAINTANK_H


class MainTank {
public:
    MainTank() : m_vx(0.0), m_vy(0.0), m_lifes(3) {}
    void Init(int x, int y);
    void Draw();
private:
    double m_start_x;       //стартовая позиция
    double m_start_y;       //

    double m_speed;         //базовая скорость
    double m_x, m_y;        //позиция игрока
    double m_vx, m_vy;      //скорость игрока
    double m_speed_ratio;   //коэффициент скорости
    double m_bullet_speed;  //скорость пули
    int m_bullet_power;     //сила пули

    int m_lifes; //кол-во жизней

    int  m_tank_width; //высота и ширина в пикселях
    int m_tank_height;
};




#endif //GAME_MAINTANK_H
