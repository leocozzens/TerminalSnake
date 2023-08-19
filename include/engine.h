#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>

#define RUNNING     1
#define EXIT_NO_ERR 0
#define EXIT_ERR    -1

struct _Board;

_Bool game_init(struct _Board *gameBoard, uint32_t winScale, uint32_t startLen);
void game_display_unit(struct _Dimension unitPoint, char visual);
int game_play_round(struct _Board *gameBoard, char **gameErr);
int game_end(struct _Board *gameBoard, int gameState, char *gameErr);

#endif