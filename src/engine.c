// C standard library
#include <stdio.h>
// Local headers
#include <shared_data.h>
#include <display.h>

_Bool game_init(Board *gameBoard, uint32_t boardScale, uint32_t startLen) {
    char *err = NULL;
    if(display_init(gameBoard, boardScale, startLen, &err)) {
        display_kill();
        fprintf(stderr, "ERROR: %s\n", err);
        return 1;
    }
    return 0;
}

void game_play_round(_Bool *gameRunning) {
    *gameRunning = 0;
    display_wait_input();
}