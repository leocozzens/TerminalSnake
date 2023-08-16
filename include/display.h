#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
struct _Board;

_Bool display_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen, char **errRet);
void display_kill(void);
char display_wait_input(void);

#endif