// C standard library
#include <stdlib.h>
#include <stdint.h>
// External libraries
#include <ncurses.h>
// Local headers
#include <shared_data.h>

#define BOARD_SCALE_FACTOR 2.5

typedef union {
    uint32_t middleVals[2];
    struct {
      uint32_t yMiddle;
      uint32_t xMiddle;  
    };
} CenterVals;

// Static functions
static _Bool determine_screen_size(Dimension *newDimension, uint32_t boardScale, uint32_t startLen, CenterVals *centers, char **errRet) {
    uint32_t yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    _Bool yScaled = 1;

    if(boardScale == 0) {
        if((yMax * BOARD_SCALE_FACTOR) > xMax) yScaled = 0;
        if(yScaled) newDimension->height = yMax;
        else newDimension->width = xMax;
    }
    else {
        if(boardScale < startLen) {
            *errRet = "Specified board size is smaller than starting snake length";
            return 1;
        }
        newDimension->height = boardScale;
    }

    if(yScaled) newDimension->width = yMax * BOARD_SCALE_FACTOR;
    else newDimension->height = xMax / BOARD_SCALE_FACTOR;
    if(newDimension->width > xMax || newDimension->height > yMax || yMax < startLen) {
        *errRet = "Terminal size too small";
        return 1;
    }

    centers->yMiddle = yMax / 2;
    centers->xMiddle = xMax / 2;
    return 0;
}

static WINDOW *make_window(Dimension *windowDimension, CenterVals centers) {
    uint32_t yOffSet = centers.yMiddle - (windowDimension->height / 2);
    uint32_t xOffset = centers.xMiddle - (windowDimension->width / 2);
    return newwin(windowDimension->height, windowDimension->width, yOffSet, xOffset);
}

// Public functions
_Bool display_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen, char **errRet) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    
    CenterVals centers;
    if(determine_screen_size(&gameBoard->windowDimension, boardScale, startLen, &centers, errRet)) return 1;

    gameBoard->gameWindow = make_window(&gameBoard->windowDimension, centers);
    refresh();
    box(gameBoard->gameWindow, 0, 0);
    wrefresh(gameBoard->gameWindow);
    return 0;
}

void display_kill(void) {
    endwin();
}

char display_wait_input(void) {
    return getch();
}