#ifndef ENGINE_H
#define ENGINE_H

// Local headers
#include <display.h>

void play_round(Board *board);
void process_input(WINDOW *boardWin);
void update_state(Board *board);

typedef struct {
    int x;
    int y;
    char icon;
} Graphic;

#endif