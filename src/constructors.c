#include <constructors.h>

void construct_apple(Board *board, uint16_t emptyY, uint16_t emptyX) {
    if(board == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Empty board structure\n");
        exit(1);
    }
    if(board->apple != NULL) {
        free(board->apple);
        board->apple = NULL;
    }
    board->apple = malloc(sizeof(Graphic));
    if(board->apple == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    board->apple->y = emptyY;
    board->apple->x = emptyX;
}

void construct_snake(Board *board, uint16_t emptyY, uint16_t emptyX) {
    board->snakeParts = malloc(sizeof(Queue));
    if (board->snakeParts == NULL) {
        endwin();
        fprintf(stderr, "ERROR: Memory allocation error\n");
        exit(1);
    }
    init_queue(board->snakeParts);
    switch(board->currentDirection) {
        case up:
            emptyY = rand() % (board->height - (START_LENGTH + 1)) + START_LENGTH;
            for(uint16_t i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, emptyY - i, emptyX);
            break;
        case down:
            emptyY = rand() % (board->height - (START_LENGTH + 1)) + 1;
            for(uint16_t i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, emptyY + i, emptyX);
            break;
        case left:
            emptyX = rand() % (board->width - (START_LENGTH + 1)) + START_LENGTH;
            for(uint16_t i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, emptyY, emptyX - i);
            break;
        case right:
            emptyX = rand() % (board->width - (START_LENGTH + 1)) + 1;
            for(uint16_t i = 0; i < START_LENGTH; i++)
                add_piece(board->snakeParts, emptyY, emptyX + i);
            break;
    }
}

void init_queue(Queue *init) {
    init->tail = NULL;
    init->head = NULL;
}

void add_piece(Queue *snakeParts, uint16_t y, uint16_t x) {
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

_Bool deque(Queue *snakeParts, Graphic *tailPiece) { // TODO: Make queue additions reuse of old snake pieces
    if(snakeParts->head == NULL) return 1;

    SnakePiece *tmp = snakeParts->tail;
    snakeParts->tail = tmp->nextPiece;
    if(snakeParts->tail == NULL) snakeParts->head = NULL;

    tailPiece->y = tmp->piece.y;
    tailPiece->x = tmp->piece.x;

    free(tmp);
    return 0;
}

void next_head(Queue *snakeParts, uint16_t *rows, uint16_t *columns, Direction currentDirection) {
    *rows = snakeParts->head->piece.y;
    *columns = snakeParts->head->piece.x;
    switch(currentDirection) {
        case up:
            (*rows)--;
            break;
        case down:
            (*rows)++;
            break;
        case left:
            (*columns)--;
            break;
        case right:
            (*columns)++;
            break;
    }
}