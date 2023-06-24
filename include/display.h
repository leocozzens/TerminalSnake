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

// Local headers
#include <shared.h>

void set_win(Board *board);
void clear_win(WINDOW *boardWin);
void print_snake(Board *board);
void print_piece(WINDOW *boardWin, SnakePiece *printPart);

#endif