// C standard libraries
#include <time.h>

// Local headers
#include <engine.h>

int main(void) { // TODO: add switches that customize board and snake elements
    // Seed rand
    srand(time(NULL));

    _Bool contGame = 1;
    _Bool initialized = 0;
    Board *board;
    while(contGame) {
        init_window(&board, &initialized);
        while(board->running) {
            play_round(board);
        }
        end_round(board);

        end_prompt(board);
    }
    return 0;
}