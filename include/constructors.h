#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

// C standard libraries
#include <stdlib.h>

// Local headers
#include <shared.h>

void construct_apple(Board *board);
void get_empty_locale(Board *board, uint16_t *y, uint16_t *x);
void new_apple(Board *board);
void construct_snake(Board *board);
void init_queue(Queue *init);
void add_piece(Queue *snakeParts, uint16_t y, uint16_t x);
void deque(Queue *snakeParts, Graphic *tailPiece);
void next_head(Queue *snakeParts, uint16_t *rows, uint16_t *columns, Direction currentDirection);

#endif