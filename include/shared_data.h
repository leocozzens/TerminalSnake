#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <stdint.h>

typedef struct {
    union {
        uint32_t y;
        uint32_t height;
    };
    union {
        uint32_t x;
        uint32_t width;
    };
} Dimension;

typedef struct _Board {
    Dimension windowDimension;
} Board;

#endif