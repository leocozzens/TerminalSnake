#ifndef SHARED_H
#define SHARED_H

#define APPLE 'A'
#define SNAKE_ICON '#'

// Ncurses terminal graphics library
#include <ncurses.h>

typedef enum { up, down, left, right } Direction;

typedef struct {
    int y;
    int x;
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
    int height;
    int width;
    Graphic *apple;
    Queue *snakeParts;
} Board;

#endif