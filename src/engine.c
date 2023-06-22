#include <engine.h>
#include <display.h>

void play_round(Board *board) {
    process_input(board->boardWin);
    update_state(board);
    wrefresh(board->boardWin);
}
void process_input(WINDOW *boardWin) {
    getch();
    // input processing
}

void update_state(Board *board) {
    Graphic apple = {.icon = 'A'};
    get_empty_locale(board, &apple.y, &apple.x);
    add_char(board->boardWin, apple.y, apple.x, apple.icon);
}

//void redraw() clear_win

//void update_state(WINDOW *boardWin);