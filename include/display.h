#ifndef DISPLAY_H
#define DISPLAY_H

// Ncurses terminal interface library
#include <ncurses.h>

// C standard libraries
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Constants
#define BOARD_SCALE 15

// Function-esque macros
#define SET_BORDER(_window) box((_window), 0, 0)
#define PRINT_HEAD(_window, _snakeParts) mvwaddch((_window), (_snakeParts)->head->piece.y, (_snakeParts)->head->piece.x, SNAKE_ICON)
#define CHECK_TAIL(_board) mvwinch((_board)->boardWin, (_board)->snakeParts->head->piece.y, (_board)->snakeParts->head->piece.x)
#define PLACE_APPLE(_board, _character) mvwaddch((_board)->boardWin, (_board)->apple->y, (_board)->apple->x, _character)

// Local headers
#include <shared.h>

void set_win(Board *board);
void clear_win(WINDOW *boardWin);
void get_empty_locale(Board *board, uint16_t *y, uint16_t *x);
void print_snake(Board *board);
void end_prompt(Board *board);

#endif