// Local headers
#include <shared_data.h>
#include <display.h>
#include <engine.h>

#define START_LENGTH 4

int main(int argc, char **argv) {
    Board gameBoard;

    if(game_init(&gameBoard, 0, START_LENGTH)) return 1;
    _Bool gameRunning;
    do {
        game_play_round(&gameRunning);
    } while(gameRunning);

    display_kill();
    return 0;
}