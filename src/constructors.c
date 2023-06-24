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
    int y;
    int x;
    get_empty_locale(board, &y, &x);
    switch(board->currentDirection) {
        case down:
            y = rand() % (board->height - (START_LENGTH + 1)) + 1;
            for(int i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, y + i, x);
            break;
        case up:
            y = rand() % (board->height - (START_LENGTH + 1)) + START_LENGTH;
            for(int i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, y - i, x);
            break;
        case left:
            x = rand() % (board->width - (START_LENGTH + 1)) + START_LENGTH;
            for(int i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, y, x - i);
            break;
        case right:
            x = rand() % (board->width - (START_LENGTH + 1)) + 1;
            for(int i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, y, x + i);
            break;
    }
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

void deque(Queue *snakeParts, Graphic *tailPiece) { // TODO: Make queue additions reuse of old snake pieces
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

void next_head(Queue *snakeParts, int *rows, int *columns, Direction currentDirection) {
    *rows = snakeParts->head->piece.y;
    *columns = snakeParts->head->piece.x;
    switch(currentDirection) {
        case down:
            (*rows)++;
            break;
        case up:
            (*rows)--;
            break;
        case left:
            (*columns)--;
            break;
        case right:
            (*columns)++;
            break;
    }
}