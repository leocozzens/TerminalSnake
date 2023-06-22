// Ncurses terminal graphics library
#include <ncurses.h>

// Local headers
#include <display.h>
#include <engine.h>

int main(void) {
    // Init window
    Board board;
    set_win(&board);
    clear_win(board.boardWin);
    
    _Bool running = 1;
    while(running) {
        play_round(&board);
    }

    //add_char(boardWin, height - 2, width - 2, '#');

    // End ncurses
    endwin();

    return 0;
}