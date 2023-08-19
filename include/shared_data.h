#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <stdint.h>

typedef enum _Direction {
    UP = -1,
    DOWN = 1,
    LEFT = -2,
    RIGHT = 2
} Direction;

typedef struct _Dimension {
    union {
        uint32_t y;
        uint32_t height;
    };
    union {
        uint32_t x;
        uint32_t width;
    };
} Dimension;

typedef struct _Graphic {
    Dimension point;
    char visual;
} Graphic;

#endif