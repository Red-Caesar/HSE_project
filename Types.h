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
    ENEMY_BIG = 3,
    ENEMY_SLOW_BONUS = 4,
    ENEMY_FAST_BONUS = 5,
    ENEMY_MEDIUM_BONUS = 6,
    ENEMY_BIG_BONUS = 7
};

enum TANK_TYPE {
    TANK_SLOW = 0,
    TANK_MEDIUM = 1
};

enum ITEM_TYPE {
    ITEM_STAR = 0,
    ITEM_LIFE = 1,
    ITEM_INVINCIBILITY = 2,
    ITEM_PROTECT = 3,
    ITEM_TIME = 4,
    ITEM_GRANADE = 5
};

enum COLOR {
    COLOR_NONE,
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
};



enum SOUNDS {
    SOUND_ONMOVE = 0,
    SOUND_FIRE = 1,
    SOUND_EXPLOSION = 2,
    SOUND_BONUS = 3,
    SOUND_GAMESTART = 4,
    SOUND_GAMEOVER = 5,
    SOUND_DIE = 6
};

enum STATE {
    GAME_OVER = 0,
    LVL_UP = 1,
    EXIT = 2
};
#endif //GAME_TYPES_H
