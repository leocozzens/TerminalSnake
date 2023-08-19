// C standard library
#include <stdlib.h>
// Local headers
#include <shared_data.h>

enum _Direction help_random_direction(void) {
    Direction randDirection;
    while((randDirection = rand() % 5 - 2) == 0); // Generates -1, 1, -2, or 2
    return randDirection;
}

struct _Dimension help_get_next_head(enum _Direction activeDirection, struct _Dimension headPoint) {
    switch(activeDirection) {
        case UP:
            headPoint.y--;
            break;
        case DOWN:
            headPoint.y++;
            break;
        case LEFT:
            headPoint.x--;
            break;
        case RIGHT:
            headPoint.x++;
            break;
    }
    return headPoint;
}