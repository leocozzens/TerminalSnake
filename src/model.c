// C standard library
#include <stdlib.h>
// Local headers
#include <board.h>

typedef struct _SnakeUnit {
    Graphic unit;
    struct _SnakeUnit *nextUnit;
} SnakeUnit;

typedef struct {
    SnakeUnit *tail;
    SnakeUnit *head;
} SnakeQueue;

// Static functions

// Public functions
void construct_food(struct _Food *gameFood, struct _Dimension emptyPoint, char foodVisual) {
    gameFood->eaten = 0;
    gameFood->graphic.point = emptyPoint;
    gameFood->graphic.visual = foodVisual;
}

