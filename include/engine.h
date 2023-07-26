#ifndef ENGINE_H
#define ENGINE_H

// System headers
#include <sys/time.h>

// Local headers
#include <constructors.h>
#include <display.h>

#define TURN_DURATION_MS 130
#define CHECK_INTERVAL_MS 10

void init_window(Board **board, _Bool *initialized);
void play_round(Board *board);
void process_input(Board *board);
void set_direction(Direction lastDirection, Direction newDirection, Direction *tempDirection);
void update_state(Board *board);
void place_head(Board *board);
void trunc_tail(Board *board);
void end_round(Board *board);

#endif