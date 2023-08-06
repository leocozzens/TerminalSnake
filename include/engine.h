#ifndef ENGINE_H
#define ENGINE_H

// Local headers
#include <constructors.h>
#include <display.h>

#define TURN_DURATION_MS 100
#define CHECK_INTERVAL_MS 10

typedef struct timeval TimeVal;

void init_window(Board **board, _Bool *initialized);
void play_round(Board *board);
TimeVal process_input(Board *board);
void set_direction(Direction lastDirection, Direction newDirection, Direction *tempDirection);
void update_state(Board *board);
void place_head(Board *board);
void trunc_tail(Board *board);
void end_round(Board *board);

#endif