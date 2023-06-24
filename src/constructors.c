#include <constructors.h>

void construct_apple(Board *board) {
    if(board == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Empty board structure\n");
        exit(1);
    }
    board->apple = malloc(sizeof(Graphic));
    if(board->apple == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    get_empty_locale(board, &(board->apple->y), &(board->apple->x));
}

void get_empty_locale(Board *board, int *y, int *x) {
    do {
        *y = rand() % board->height;
        *x = rand() % board->width;
    } while(mvwinch(board->boardWin, *y, *x) != ' ');
}

void new_apple(Board *board) {
    if(board->apple != NULL) {
        mvwaddch(board->boardWin, board->apple->y, board->apple->x, ' ');
        free(board->apple);
        board->apple = NULL;
    }
    construct_apple(board);
    mvwaddch(board->boardWin, board->apple->y, board->apple->x, APPLE);
    wrefresh(board->boardWin);
}

void construct_snake(Board *board) {
    board->snakeParts = malloc(sizeof(Queue));
    if (board->snakeParts == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    init_queue(board->snakeParts);
    add_piece(board->snakeParts, 10, 10);
    add_piece(board->snakeParts, 9, 10);
    add_piece(board->snakeParts, 8, 10);
    add_piece(board->snakeParts, 7, 10);
}

void init_queue(Queue *init) {
    init->tail = NULL;
    init->head = NULL;
}

void add_piece(Queue *snakeParts, int y, int x) {
    SnakePiece *newPiece = malloc(sizeof(SnakePiece));
    if(newPiece == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    newPiece->piece.y = y;
    newPiece->piece.x = x;
    newPiece->nextPiece = NULL;

    if(snakeParts->head != NULL) snakeParts->head->nextPiece = newPiece;
    else snakeParts->tail = newPiece;
    snakeParts->head = newPiece;
}

void deque(Queue *snakeParts, Graphic *tailPiece) {
    if(snakeParts->head == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Attempted to deque empty queue\n");
        exit(1);
    }
    SnakePiece *tmp = snakeParts->tail;
    snakeParts->tail = tmp->nextPiece;
    if(snakeParts->tail == NULL) snakeParts->head = NULL;

    tailPiece->y = tmp->piece.y;
    tailPiece->x = tmp->piece.x;

    free(tmp);
}

SnakePiece *next_head(Queue *snakeParts, Direction currentDirection) {
    SnakePiece *nextHead = malloc(sizeof(SnakePiece));
    if(nextHead == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    int rows = snakeParts->head->piece.y;
    int columns = snakeParts->head->piece.x;
    switch(currentDirection) {
        case down:
            rows++;
            break;
        case up:
            rows--;
            break;
        case left:
            columns--;
            break;
        case right:
            columns++;
            break;
    }

    nextHead->piece.y = rows;
    nextHead->piece.x = columns;
    return nextHead;
}