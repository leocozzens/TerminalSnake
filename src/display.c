#include <display.h>

void set_win(WINDOW **win) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int height = BOARD_SCALE;
    int width = height * 2.5;

    if(height > maxY || width > maxX) {
        height = maxY;
        width = height * 2.5;
        if(width > maxX || maxY < 1) {
            fprintf(stderr, "ERROR: Terminal size too small");
            endwin();
            exit(1);
        }
    }
    
    *win = newwin(height, width, (maxY/2) - (height/2), (maxX/2) - (width/2));

    refresh();

    box(*win, 0, 0);
    curs_set(0);
    wrefresh(*win);
}