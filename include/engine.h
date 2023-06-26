#ifndef ENGINE_H
#define ENGINE_H

// System headers
#include <sys/time.h>

// Local headers
#include <constructors.h>
#include <display.h>

#define TURN_DURATION 130 // In milliseconds

void init_window(Board **board, _Bool *initialized);
void play_round(Board *board);
void process_input(Board *board);
double get_elapsed_time(void);
void set_direction(Direction lastDirection, Direction newDirection, Direction *tempDirection);
void update_state(Board *board);
void place_head(Board *board);
void trunc_tail(Board *board);
void end_round(Board *board);

#endif