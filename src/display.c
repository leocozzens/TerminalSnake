// C standard library
#include <stdlib.h>
#include <stdint.h>
// External libraries
#include <ncurses.h>
// Local headers
#include <shared_data.h>

#define BOARD_SCALE_FACTOR 2.5

// Static functions
static _Bool determine_screen_size(Dimension *newDimension, uint32_t boardScale, uint32_t startLen, char **errRet) {
    uint32_t yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    if(boardScale == 0) newDimension->height = yMax;
    else {
        if(boardScale < startLen) {
            *errRet = "Specified board size is smaller than starting snake length";
            return 1;
        }
        newDimension->height = boardScale;
    }

    newDimension->width = yMax * BOARD_SCALE_FACTOR;
    if(newDimension->width > xMax || newDimension->height > yMax || yMax < startLen) {
        *errRet = "Terminal size too small";
        return 1;
    }

    return 0;
}

// Public functions
_Bool display_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen, char **errRet) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    if(determine_screen_size(&gameBoard->windowDimension, boardScale, startLen, errRet)) return 1;

    return 0;
}

void display_kill(void) {
    endwin();
}

char display_wait_input(void) {
    return getch();
}