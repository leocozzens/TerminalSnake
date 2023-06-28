#ifndef SHARED_H
#define SHARED_H

// Constants
#define APPLE 'A'
#define SNAKE_ICON '#'
#define START_LENGTH 4

// Ncurses terminal graphics library
#include <ncurses.h>

// Standard C libraries
#include <stdint.h>

typedef enum { up = -1, down = 1, left = -2, right = 2 } Direction;

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
    WINDOW *scoreBoard;
    uint64_t score;
    _Bool running;
    uint16_t height;
    uint16_t width;
    Direction currentDirection;
    Graphic *apple;
    Queue *snakeParts;
} Board;

#endif