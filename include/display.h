#ifndef DISPLAY_H
#define DISPLAY_H

// Ncurses terminal interface library
#include <ncurses.h>

// C standard libraries
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BOARD_SCALE 15
#define MIN_HEIGHT 5
#define SET_BORDER(window) box(window, 0, 0)

typedef struct {
    int x;
    int y;
    char icon;
} Graphic;

typedef struct {
    WINDOW *boardWin;
    int height;
    int width;
    Graphic *apple;
} Board;

void set_win(Board *board);
void clear_win(WINDOW *boardWin);
void get_empty_locale(Board *board, int *y, int *x);

#endif