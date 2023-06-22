#include <display.h>

void set_win(WINDOW **boardWin, int *height, int *width) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    *height = BOARD_SCALE;
    *width = *height * 2.5;

    if(*height > maxY || *width > maxX) {
        *height = maxY;
        *width = *height * 2.5;
        if(*width > maxX || maxY < MIN_HEIGHT) {
            fprintf(stderr, "ERROR: Terminal size too small");
            endwin();
            exit(1);
        }
    }

    *boardWin = newwin(*height, *width, (maxY/2) - (*height/2), (maxX/2) - (*width/2));

    refresh();
}

void clear_win(WINDOW *boardWin) {
    wclear(boardWin);
    SET_BORDER(boardWin);
    curs_set(0);
    wrefresh(boardWin);
}

void add_char(WINDOW *boardWin, int y, int x, char out) {
    mvwaddch(boardWin, y, x, out);
    wrefresh(boardWin);
}