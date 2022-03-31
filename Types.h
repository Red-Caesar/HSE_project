#ifndef GAME_TYPES_H
#define GAME_TYPES_H


enum DIRECTION {
    DIR_RIGHT = 0,
    DIR_LEFT = 1,
    DIR_DOWN = 2,
    DIR_UP = 3,
};

enum ENEMY_TYPE {
    ENEMY_SLOW = 0,
    ENEMY_MEDIUM = 1,
    ENEMY_FAST = 2,
    ENEMY_BIG = 3
};

enum TANK_TYPE {
    TANK_SLOW = 0,
    TANK_MEDIUM = 1
};

enum STATE {
    GAME_OVER = 0,
    LVL_UP = 1,
    EXIT = 2
};
#endif //GAME_TYPES_H
