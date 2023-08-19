#ifndef FOOD_H
#define FOOD_H

#include <shared_data.h>

typedef struct _Food {
    Graphic graphic;
    _Bool eaten;
} Food;

typedef struct _FoodTypes {
    char *types;
    uint16_t typeCount;
} FoodTypes;

#endif