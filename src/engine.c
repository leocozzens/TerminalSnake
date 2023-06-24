#include <engine.h>

Board *init_window(void) {
    Board *board = malloc(sizeof(Board));
    board->apple = NULL;
    board->snakeParts = NULL;
    set_win(board);
    clear_win(board->boardWin);
    construct_apple(board);
    mvwaddch(board->boardWin, board->apple->y, board->apple->x, APPLE);

    construct_snake(board);
    print_snake(board);

    return board;
}

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
    SnakePiece *nextHead = next_head(board->snakeParts, board->currentDirection);
    add_piece(board->snakeParts, nextHead->piece.y, nextHead->piece.x);
    print_piece(board->boardWin, nextHead);
    free(nextHead);
    nextHead = NULL;

    Graphic tailPiece;
    deque(board->snakeParts, &tailPiece);
    mvwaddch(board->boardWin, tailPiece.y, tailPiece.x, ' ');
    new_apple(board);
}