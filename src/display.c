// C standard library
#include <stdlib.h>
#include <stdint.h>
// External libraries
#include <ncurses.h>
// Local headers
#include <shared_data.h>

#define BOARD_SCALE_FACTOR 2.5
#define BORDER_SIZE        2

#define EMPTY_SPACE        ' '

// Static functions
static _Bool determine_screen_size(Dimension *newDimension, uint32_t winScale, uint32_t startLen, Dimension *centerVals, char **errRet) {
    uint32_t yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    _Bool yScaled = 1;

    if(winScale == 0) {
        if((yMax * BOARD_SCALE_FACTOR) > xMax) yScaled = 0;
        if(yScaled) newDimension->height = yMax;
        else newDimension->width = xMax;
    }
    else {
        if(winScale < (startLen + BORDER_SIZE)) {
            *errRet = "Specified board size is smaller than starting snake length";
            return 1;
        }
        newDimension->height = winScale;
    }

    if(yScaled) newDimension->width = yMax * BOARD_SCALE_FACTOR;
    else newDimension->height = xMax / BOARD_SCALE_FACTOR;
    if(newDimension->width > xMax || newDimension->height > yMax || newDimension->height < (startLen + BORDER_SIZE)) {
        *errRet = "Terminal size too small";
        return 1;
    }

    centerVals->y = yMax / 2;
    centerVals->x = xMax / 2;
    return 0;
}

static WINDOW *make_window(Dimension winDim, Dimension centerVals) {
    uint32_t yOffSet = centerVals.y - (winDim.height / 2);
    uint32_t xOffset = centerVals.x - (winDim.width / 2);
    return newwin(winDim.height, winDim.width, yOffSet, xOffset);
}

// Public functions
_Bool display_init(WINDOW **gameWin, struct _Dimension *winDim, uint32_t boardScale, uint32_t startLen, char **errRet) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    
    Dimension centerVals;
    if(determine_screen_size(winDim, boardScale, startLen, &centerVals, errRet)) return 1;

    *gameWin = make_window(*winDim, centerVals);
    refresh();
    box(*gameWin, 0, 0);
    wrefresh(*gameWin);
    return 0;
}

Dimension display_get_empty_locale(WINDOW *win, struct _Dimension winDim) {
    Dimension newDim;
    do {
        newDim.y = rand() % (winDim.height - BORDER_SIZE) + BORDER_SIZE / 2;
        newDim.x = rand() % (winDim.width - BORDER_SIZE) + BORDER_SIZE / 2;
    } while(mvwinch(win, newDim.y, newDim.x) != EMPTY_SPACE);
    return newDim;
}

void display_print_graphic(struct _Graphic *graphic, WINDOW *win) {
    mvwaddch(win, graphic->point.y, graphic->point.x, graphic->visual);
}

void display_print_object(struct _Dimension objectPoint, char visual, WINDOW *win) {
    mvwaddch(win, objectPoint.y, objectPoint.x, visual);
}

void display_clear_object(struct _Dimension objectPoint, WINDOW *win) {
    mvwaddch(win, objectPoint.y, objectPoint.x, EMPTY_SPACE);
}

void display_refresh_win(WINDOW *win) {
    wrefresh(win);
}

void display_kill(void) {
    endwin();
}

char display_wait_input(void) {
    return getch();
}