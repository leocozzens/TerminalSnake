// Local headers
#include <engine.h>

int main(void) {
    Board *board = init_window();
    
    board->currentDirection = up;
    _Bool running = 1;
    while(running) {
        play_round(board);
    }

    endwin();
    return 0;
}