// Local headers
#include <display.h>
#include <engine.h>

int main(void) {
    Board *board = init_window();
    
    _Bool running = 1;
    Direction currentDirection = down;
    while(running) {
        play_round(board);
    }

    //add_char(boardWin, height - 2, width - 2, '#');

    // End ncurses
    endwin();

    return 0;
}