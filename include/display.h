#ifndef DISPLAY_H
#define DISPLAY_H

// Ncurses terminal interface library
#include <ncurses.h>

// C standard libraries
#include <stdlib.h>

#define BOARD_SCALE 15
#define MIN_HEIGHT 5
#define SET_BORDER(window) box(window, 0, 0)

void set_win(WINDOW **boardWin, int *height, int *width);
void clear_win(WINDOW *boardWin);
void add_char(WINDOW *boardWin, int y, int x, char out);

#endif