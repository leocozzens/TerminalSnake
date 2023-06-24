#include <display.h>

void set_win(Board *board) {
    // Ncurses init
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    
    // Seed rand
    srand(time(NULL));

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    board->height = BOARD_SCALE;
    board->width = board->height * 2.5;

    if(board->height > maxY || board->width > maxX) {
        board->height = maxY;
        board->width = board->height * 2.5;
        if(board->width > maxX || maxY < MIN_HEIGHT) {
            endwin();
            fprintf(stderr, "ERROR: Terminal size too small");
            exit(1);
        }
    }

    board->boardWin = newwin(board->height, board->width, (maxY/2) - (board->height/2), (maxX/2) - (board->width/2));

    refresh();
}

void clear_win(WINDOW *boardWin) {
    wclear(boardWin);
    SET_BORDER(boardWin);
    wrefresh(boardWin);
}

//void print_graphic