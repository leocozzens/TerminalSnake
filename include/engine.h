#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
struct _Board;

_Bool game_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen);
void game_play_round(_Bool *gameRunning);
void game_end(void);

#endif