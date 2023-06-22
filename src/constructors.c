#include <constructors.h>

void construct_apple(Board *board) {
    board->apple = malloc(sizeof(Graphic));
    if(board->apple == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    get_empty_locale(board, &(board->apple->y), &(board->apple->x));
    board->apple->icon = 'A';
}