// Local headers
#include <engine.h>

int main(void) {
    _Bool contGame = 1;
    _Bool initialized = 0;
    Board *board;
    while(contGame) {
        init_window(&board, initialized);
        initialized = 1;
        while(board->running) {
            play_round(board);
        }

        end_round(board);
    }
    return 0;
}