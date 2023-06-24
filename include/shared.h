#ifndef SHARED_H
#define SHARED_H

#define APPLE 'A'
#define SNAKE_ICON '#'

#define START_LENGTH 4

// Ncurses terminal graphics library
#include <ncurses.h>

// Standard C libraries
#include <stdint.h>

typedef enum { up, down, left, right } Direction;

typedef struct {
    uint16_t y;
    uint16_t x;
} Graphic;

typedef struct SnakePiece {
    Graphic piece;
    struct SnakePiece *nextPiece;
} SnakePiece;

typedef struct {
    SnakePiece *tail;
    SnakePiece *head;
} Queue;

typedef struct {
    WINDOW *boardWin;
    _Bool running;
    size_t height;
    size_t width;
    Direction currentDirection;
    Graphic *apple;
    Queue *snakeParts;
} Board;

#endif