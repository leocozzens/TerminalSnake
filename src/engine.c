// C standard library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Local headers
#include <board.h>
#include <engine.h>
#include <display.h>
#include <model.h>
#include <helpers.h>

#define APPLE   'A'
#define PEAR    'P'

// Static functions
static WINDOW* gameWin;
static void new_food(Board *gameBoard) {
    model_construct_food(&gameBoard->gameFood, display_get_empty_locale(gameWin, gameBoard->windowDimension), gameBoard->foodTypes.types[rand() % gameBoard->foodTypes.typeCount]);
    display_print_graphic(&gameBoard->gameFood.graphic, gameWin);
}

static void update_state(Board *gameBoard) {
    Dimension nextHead = help_get_next_head(gameBoard->activeDirection, model_get_head());
    switch(display_check_collision(nextHead, gameBoard->foodTypes.types, gameBoard->foodTypes.typeCount, gameWin)) {
        case NONE:
            // display clear tail
            // model recycle unit
            break;
        case FOOD:
            // model make new unit 
            break;
        case OTHER:
            // end game
            break;
    }
    // model add head
    // display print head
    if(gameBoard->gameFood.eaten) {
        display_clear_object(gameBoard->gameFood.graphic.point, gameWin);
        new_food(gameBoard);
    }
    display_refresh_win(gameWin);
}

static void handle_input(Board *gameBoard) {
    display_wait_input();
}

// Public functions
_Bool game_init(struct _Board *gameBoard, uint32_t winScale, uint32_t startLen) {
    char *err = NULL;
    srand(time(NULL));
    if(display_init(&gameWin, &gameBoard->windowDimension, winScale, startLen, &err)) {
        display_kill();
        fprintf(stderr, "ERROR: %s\n", err);
        return 1;
    }
    gameBoard->activeDirection = help_random_direction();
    model_init_snake(gameBoard->activeDirection, gameBoard->windowDimension, startLen, BORDER_SIZE, '#', '#');
    model_init_food_types(&gameBoard->foodTypes);
    model_add_food_type(&gameBoard->foodTypes, APPLE);
    model_add_food_type(&gameBoard->foodTypes, PEAR); // TODO: Handle exceptions here
    model_run_for_each(game_display_unit);
    new_food(gameBoard);
    display_refresh_win(gameWin);
    return 0;
}

void game_display_unit(struct _Dimension unitPoint, char visual) {
    display_print_object(unitPoint, visual, gameWin);
}

int game_play_round(struct _Board *gameBoard, char **gameErr) {
    handle_input(gameBoard);
    update_state(gameBoard);
    return EXIT_NO_ERR;
}

int game_end(struct _Board *gameBoard, int gameState, char *gameErr) {
    display_kill();
    if(gameState == EXIT_ERR) {
        fprintf(stderr, "ERROR: %s\n", gameErr);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}