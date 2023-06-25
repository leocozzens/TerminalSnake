#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

// C standard libraries
#include <stdlib.h>

// Local headers
#include <shared.h>

void construct_apple(Board *board, uint16_t emptyY, uint16_t emptyX);
void construct_snake(Board *board, uint16_t emptyY, uint16_t emptyX);
void init_queue(Queue *init);
void add_piece(Queue *snakeParts, uint16_t y, uint16_t x);
_Bool deque(Queue *snakeParts, Graphic *tailPiece);
void next_head(Queue *snakeParts, uint16_t *rows, uint16_t *columns, Direction currentDirection);

#endif