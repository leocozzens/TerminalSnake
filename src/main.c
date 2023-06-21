// Ncurses terminal graphics library
#include <ncurses.h>

// Local headers
#include <display.h>

int main(void) {
    // Initialize ncurses
    initscr();
    cbreak();

    // Turn off character echoing
    noecho();

    WINDOW *win = NULL;
    set_win(&win);

    // Await user input;
    getch();


    // End ncurses
    endwin();

    return 0;
}