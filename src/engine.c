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
    process_input(board);
    update_state(board);
    wrefresh(board->boardWin);
}

void process_input(Board *board) {
    char input = wgetch(board->boardWin);
    switch(input) {
        case 's':
            board->currentDirection = down;
            break;
        case 'w':
            board->currentDirection = up;
            break;
        case 'a':
            board->currentDirection = left;
            break;
        case 'd':
            board->currentDirection = right;
            break;
        default:
            break;
    }
}

void update_state(Board *board) {
    place_head(board);
    char next_char = mvwinch(board->boardWin, board->snakeParts->head->piece.y, board->snakeParts->head->piece.x);
    if(next_char != ' ') {
        switch(next_char) {
            case APPLE:
                new_apple(board);
                break;
            default:
                endwin();
                exit(0);
                break;
        }
    }
    else trunc_tail(board);

    print_head(board->boardWin, board->snakeParts);
}

void place_head(Board *board) {
    Graphic *nextHead = next_head(board->snakeParts, board->currentDirection);
    add_piece(board->snakeParts, nextHead->y, nextHead->x); // TODO: have add_piece take graphic and add it to new piece
    free(nextHead);
}


void trunc_tail(Board *board) {
    Graphic tailPiece;
    deque(board->snakeParts, &tailPiece);
    mvwaddch(board->boardWin, tailPiece.y, tailPiece.x, ' ');
}