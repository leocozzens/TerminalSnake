#ifndef BOARD_H
#define BOARD_H

#include <shared_data.h>

typedef struct _win_st WINDOW;

typedef struct _Food {
    Graphic graphic;
    _Bool eaten;
} Food;

typedef struct _Board {
    Direction activeDirection;
    Food gameFood;
    WINDOW *gameWindow;
    Dimension windowDimension;
} Board;

#endif