#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define BORDER_SIZE 2

typedef struct _win_st WINDOW;
struct _Dimension;
struct _Graphic;
struct _Board;

_Bool display_init(WINDOW **gameWin, struct _Dimension *winDim, uint32_t winScale, uint32_t startLen, char **errRet);
Dimension display_get_empty_locale(WINDOW *win, struct _Dimension winDim);
void display_print_graphic(struct _Graphic *graphic, WINDOW *win);
void display_print_object(struct _Dimension objectPoint, char visual, WINDOW *win);
void display_clear_object(struct _Dimension objectPoint, WINDOW *win);
void display_refresh_win(WINDOW *win);
void display_kill(void);
char display_wait_input(void);

#endif