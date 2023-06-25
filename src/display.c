#include <display.h>

void set_win(Board *board) {
    // Ncurses init
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    size_t maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    board->height = BOARD_SCALE; // TODO: Add scaling default, and custom size determined by switch, ensure overflow protection
    board->width = board->height * 2.5;

    if(board->height > maxY || board->width > maxX) {
        board->height = maxY;
        board->width = board->height * 2.5;
        if(board->width > maxX || maxY < (START_LENGTH + 2)) { // Added 2 to allow for both borders
            endwin();
            fprintf(stderr, "ERROR: Terminal size too small");
            exit(1);
        }
    }

    board->boardWin = newwin(board->height, board->width, (maxY/2) - (board->height/2), (maxX/2) - (board->width/2));

    keypad(board->boardWin, 1);
    refresh();
}

void clear_win(WINDOW *boardWin) {
    wclear(boardWin);
    SET_BORDER(boardWin);
    wrefresh(boardWin);
}

void get_empty_locale(Board *board, uint16_t *y, uint16_t *x) { // TODO: Add counter to check if board is full
    do {
        *y = rand() % (board->height - 1);
        *x = rand() % (board->width - 1);
    } while(mvwinch(board->boardWin, *y, *x) != ' ');
}

void print_snake(Board *board) {
    SnakePiece *tmp = board->snakeParts->tail;
    while(tmp != NULL) {
        mvwaddch(board->boardWin, tmp->piece.y, tmp->piece.x, SNAKE_ICON);
        tmp = tmp->nextPiece;
    }
}

void print_head(WINDOW *boardWin, Queue *snakeParts) {
    mvwaddch(boardWin, snakeParts->head->piece.y, snakeParts->head->piece.x, SNAKE_ICON);
}