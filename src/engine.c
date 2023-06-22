#include <engine.h>

void play_round(Board *board) {
    process_input(board->boardWin);
    update_state(board);
    wrefresh(board->boardWin);
}
void process_input(WINDOW *boardWin) {
    char input = wgetch(boardWin);
    // input processing
}

void update_state(Board *board) {
    if(board->apple != NULL) {
        mvwaddch(board->boardWin, board->apple->y, board->apple->x, ' ');
        free(board->apple);
        board->apple = NULL;
    }
    construct_apple(board);
    mvwaddch(board->boardWin, board->apple->y, board->apple->x, board->apple->icon);
    wrefresh(board->boardWin);
}