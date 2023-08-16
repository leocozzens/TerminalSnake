// C standard library
#include <stdio.h>
#include <stdlib.h>
// Local headers
#include <shared_data.h>
#include <display.h>

#define RUNNING     1
#define EXIT_NO_ERR 0
#define EXIT_ERR    -1

_Bool game_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen) {
    char *err = NULL;
    if(display_init(gameBoard, boardScale, startLen, &err)) {
        display_kill();
        fprintf(stderr, "ERROR: %s\n", err);
        return 1;
    }
    return 0;
}

int game_play_round(char **gameErr) {
    display_wait_input();
    return EXIT_NO_ERR;
}

int game_end(struct _Board *gameBoard, int gameState, char *gameErr) {
    display_kill();
    free(gameBoard->windowDimension);
    if(gameState == EXIT_ERR) {
        fprintf(stderr, "ERROR: %s\n", gameErr);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}