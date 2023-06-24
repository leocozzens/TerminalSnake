#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

// C standard libraries
#include <stdlib.h>

// Local headers
#include <shared.h>

void construct_apple(Board *board);
void get_empty_locale(Board *board, int *y, int *x);
void new_apple(Board *board);
void construct_snake(Board *board);
void init_queue(Queue *init);
void add_piece(Queue *snakeParts, int y, int x);
void deque(Queue *snakeParts, Graphic *tailPiece);
SnakePiece *next_head(Queue *snakeParts, Direction currentDirection);

#endif