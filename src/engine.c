// C standard library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Local headers
#include <board.h>
#include <display.h>
#include <model.h>

#define RUNNING     1
#define EXIT_NO_ERR 0
#define EXIT_ERR    -1

#define APPLE       'A'
#define PEAR        'P'

// Static functions
static void new_food(Board *gameBoard) {
    construct_food(&gameBoard->gameFood, display_get_empty_locale(gameBoard->gameWindow, gameBoard->windowDimension), APPLE);
    display_print_object(&gameBoard->gameFood.graphic, gameBoard->gameWindow);
}

static void update_state(Board *gameBoard) {
    if(gameBoard->gameFood.eaten) {
        display_clear_object(gameBoard->gameFood.graphic.point, gameBoard->gameWindow);
        new_food(gameBoard);
    }
    display_refresh_win(gameBoard->gameWindow);
}

static void handle_input(Board *gameBoard) {
    display_wait_input();
}


// Public functions
_Bool game_init(struct _Board *gameBoard, uint32_t winScale, uint32_t startLen) {
    char *err = NULL;
    srand(time(NULL));
    if(display_init(&gameBoard->gameWindow, &gameBoard->windowDimension, winScale, startLen, &err)) {
        display_kill();
        fprintf(stderr, "ERROR: %s\n", err);
        return 1;
    }
    new_food(gameBoard);
    return 0;
}

int game_play_round(struct _Board *gameBoard, char **gameErr) {
    update_state(gameBoard);
    handle_input(gameBoard);
    return RUNNING;
}

int game_end(struct _Board *gameBoard, int gameState, char *gameErr) {
    display_kill();
    if(gameState == EXIT_ERR) {
        fprintf(stderr, "ERROR: %s\n", gameErr);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}