// Local headers
#include <shared_data.h>
#include <engine.h>

#define EXIT_FAILURE 1

#define BOARD_SCALE  0
#define START_LENGTH 4

int main(int argc, char **argv) {
    Board gameBoard = { 0x0 };
    if(game_init(&gameBoard, BOARD_SCALE, START_LENGTH)) return EXIT_FAILURE;

    int gameState;
    char *gameErr;
    do { gameState = game_play_round(&gameErr); } while(gameState == RUNNING);

    return game_end(&gameBoard, gameState, gameErr);
}