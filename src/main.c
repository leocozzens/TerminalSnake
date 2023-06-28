// C standard libraries
#include <string.h>

// Local headers
#include <engine.h>

int main(int argc, char **argv) { // TODO: add switches that customize board and snake elements
    if(argc > 1) {
        if(strlen(argv[1]) > 1) if(argv[1][1] == 'h') {
            printf("TerminalSnake [OPTIONS]...\n");
            exit(0);
        }
    }
    // Seed rand
    srand(time(NULL));

    _Bool contGame = 1;
    _Bool initialized = 0;
    Board *board;
    while(contGame) {
        init_window(&board, &initialized); // TODO: Add resize conditions for board window
        while(board->running) {
            play_round(board);
        }
        end_round(board);
    }
    return 0;
}