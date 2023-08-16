// C standard library
#include <stdlib.h>
#include <stdint.h>
// External libraries
#include <ncurses.h>
// Local headers
#include <shared_data.h>

#define BOARD_SCALE_FACTOR 2.5

struct _Dimension {
    union {
        uint32_t y;
        uint32_t height;
    };
    union {
        uint32_t x;
        uint32_t width;
    };
};

// Static functions
static Dimension *determine_screen_size(uint32_t boardScale, uint32_t startLen, char **errRet) {
    uint32_t yMax, xMax, height, width;
    getmaxyx(stdscr, yMax, xMax);

    if(boardScale == 0) height = yMax;
    else {
        if(boardScale < startLen) {
            *errRet = "Specified board size is smaller than starting snake length";
            return NULL;
        }
        height = boardScale;
    }

    width = yMax * BOARD_SCALE_FACTOR;
    if(width > xMax || height < startLen) {
        *errRet = "Terminal size too small";
        return NULL;
    }

    Dimension *windowDimension = malloc(sizeof(Dimension));
    windowDimension->height = height;
    windowDimension->width = width;

    return windowDimension;
}

// Public functions
_Bool display_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen, char **errRet) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    Dimension *windowDimension = determine_screen_size(boardScale, startLen, errRet);
    if(windowDimension == NULL) return 1;

    return 0;
}

void display_kill(void) {
    endwin();
}

char display_wait_input(void) {
    return getch();
}