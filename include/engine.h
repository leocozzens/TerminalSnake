#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>

typedef struct _Board Board;

_Bool game_init(Board *gameBoard, uint32_t boardScale, uint32_t startLen);
void game_play_round(_Bool *gameRunning);

#endif