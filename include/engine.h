#ifndef ENGINE_H
#define ENGINE_H

// Local headers
#include <constructors.h>
#include <display.h>


Board *init_window(void);
void play_round(Board *board);
void process_input(Board *board);
void update_state(Board *board);
void place_head(Board *board);
void trunc_tail(Board *board);

#endif