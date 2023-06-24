#include <engine.h>

Board *init_window(void) {
    Board *board = malloc(sizeof(Board));
    board->apple = NULL;
    board->snakeParts = NULL;
    set_win(board);
    clear_win(board->boardWin);
    board->currentDirection = rand() % 4;

    construct_snake(board);
    print_snake(board);
    wrefresh(board->boardWin);

    construct_apple(board);
    mvwaddch(board->boardWin, board->apple->y, board->apple->x, APPLE);

    return board;
}

void play_round(Board *board) {
    process_input(board);
    update_state(board);
    wrefresh(board->boardWin);
}

void process_input(Board *board) {
    int16_t input = wgetch(board->boardWin);
    switch(input) {
        case KEY_UP:
        case 'w':
            board->currentDirection = up;
            break;
        case KEY_DOWN:
        case 's':
            board->currentDirection = down;
            break;
        case KEY_LEFT:
        case 'a':
            board->currentDirection = left;
            break;
        case KEY_RIGHT:
        case 'd':
            board->currentDirection = right;
            break;
        default:
            break;
    }
}

void update_state(Board *board) {
    place_head(board);
    char nextChar = CHECK_TAIL(board);
    if(nextChar != ' ') {
        switch(nextChar) {
            case APPLE:
                new_apple(board);
                break;
            case SNAKE_ICON:
                trunc_tail(board);
                if(CHECK_TAIL(board) == SNAKE_ICON) {
                    endwin();
                    exit(0);
                }
                break;
            default:
                //end_game(board->boardWin);
                endwin();
                exit(0);
                break;
        }
    }
    else trunc_tail(board);

    print_head(board->boardWin, board->snakeParts);
}

void place_head(Board *board) {
    uint16_t y;
    uint16_t x;
    next_head(board->snakeParts, &y, &x, board->currentDirection);
    add_piece(board->snakeParts, y, x);
}


void trunc_tail(Board *board) {
    Graphic tailPiece;
    deque(board->snakeParts, &tailPiece);
    mvwaddch(board->boardWin, tailPiece.y, tailPiece.x, ' ');
}