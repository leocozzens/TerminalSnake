#ifndef BOARD_H
#define BOARD_H

#include <food.h>

typedef struct _Board {
    Direction activeDirection;
    Food gameFood;
    FoodTypes foodTypes;
    Dimension windowDimension;
} Board;

#endif