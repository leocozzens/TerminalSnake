// Ncurses terminal graphics library
#include <ncurses.h>

// Local headers
#include <display.h>

int main(void) {
    // Init
    initscr();
    cbreak();
    noecho();

    // Init window
    WINDOW *boardWin = NULL;
    int height;
    int width;
    set_win(&boardWin, &height, &width);
    clear_win(boardWin);


    //add_char(boardWin, height - 2, width - 2, '#');

    getch();
    // End ncurses
    endwin();

    return 0;
}