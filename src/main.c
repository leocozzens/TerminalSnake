// Local headers
#include <shared_data.h>
#include <engine.h>

#define BOARD_SCALE  0
#define START_LENGTH 4

int main(int argc, char **argv) {
    Board gameBoard;

    if(game_init(&gameBoard, BOARD_SCALE, START_LENGTH)) return 1;
    _Bool gameRunning;
    do {
        game_play_round(&gameRunning);
    } while(gameRunning);

    game_end();
    return 0;
}