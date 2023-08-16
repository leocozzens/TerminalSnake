#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>

#define RUNNING     1
#define EXIT_NO_ERR 0
#define EXIT_ERR    -1

struct _Board;

_Bool game_init(struct _Board *gameBoard, uint32_t boardScale, uint32_t startLen);
int game_play_round(char **gameErr);
int game_end(struct _Board *gameBoard, int gameState, char *gameErr);

#endif