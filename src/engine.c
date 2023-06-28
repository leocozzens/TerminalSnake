#include <engine.h>

void init_window(Board **board, _Bool *initialized) {
    if(!(*initialized)) {
        *board = malloc(sizeof(Board));
        set_win(*board);
    }
    (*board)->apple = NULL;
    (*board)->snakeParts = NULL;
    clear_score((*board)->scoreBoard);
    clear_win((*board)->boardWin);
    (*board)->running = 1;
    while(((*board)->currentDirection = rand() % 5 - 2) == 0); // Generates -1, 1, 2, or -2
    (*board)->score = 0;

    uint16_t emptyY, emptyX;
    get_empty_locale(*board, &emptyY, &emptyX); // Snake must be placed first as there is no locality checking for subsequant tail pieces
    construct_snake(*board, emptyY, emptyX);
    print_snake(*board);
    wrefresh((*board)->boardWin);

    get_empty_locale(*board, &emptyY, &emptyX);
    construct_apple(*board, emptyY, emptyX);
    PLACE_APPLE(*board, APPLE);
    wrefresh((*board)->boardWin);

    *initialized = 1;
}

void play_round(Board *board) {
    process_input(board);
    update_state(board);
    wrefresh(board->boardWin);
}

void process_input(Board *board) {
    Direction tempDirection = board->currentDirection;
    double startTime = get_elapsed_time();
    wtimeout(board->boardWin, 10);
    do {
        int16_t input = wgetch(board->boardWin);
        switch(input) {
            case KEY_UP:
            case 'w':
                set_direction(board->currentDirection, up, &tempDirection);
                break;
            case KEY_DOWN:
            case 's':
                set_direction(board->currentDirection, down, &tempDirection);
                break;
            case KEY_LEFT:
            case 'a':
                set_direction(board->currentDirection, left, &tempDirection);
                break;
            case KEY_RIGHT:
            case 'd':
                set_direction(board->currentDirection, right, &tempDirection);
                break;
            case 'p':
                wtimeout(board->boardWin, -1);
                while(wgetch(board->boardWin) != 'p'); // TODO: 3... 2... 1... Pause on first frame
                wtimeout(board->boardWin, TURN_DURATION);
                continue;
                break;
            default:
                break;
        }
    } while((get_elapsed_time() - startTime) < TURN_DURATION);
    board->currentDirection = tempDirection;
}

double get_elapsed_time( void) { // TODO: Add portable windows method
    struct timeval start;
    gettimeofday(&start, NULL);
    return (start.tv_sec * 1000.0) + (start.tv_usec / 1000.0);
}

void set_direction(Direction lastDirection, Direction newDirection, Direction *tempDirection) {
    if(lastDirection + newDirection != 0) *tempDirection = newDirection;
    else *tempDirection = lastDirection;
}

void update_state(Board *board) {
    place_head(board);
    char nextChar = CHECK_TAIL(board);
    if(nextChar != ' ') {
        switch(nextChar) {
            case APPLE:
                uint16_t emptyY, emptyX;
                do { // Ensure that the new apple position is not the same as the next snake head position that hasnt yet been printed
                    get_empty_locale(board, &emptyY, &emptyX);// TODO: Add counter to check if board is full
                } while((emptyY == board->snakeParts->head->piece.y) && (emptyX == board->snakeParts->head->piece.x));

                construct_apple(board, emptyY, emptyX);
                PLACE_APPLE(board, APPLE);
                board->score += 10;
                update_score(board);
                break;
            case SNAKE_ICON:
                trunc_tail(board);
                if(CHECK_TAIL(board) == SNAKE_ICON) 
                    board->running = 0;
                break;
            default:
                board->running = 0;
                break;
        }
    }
    else trunc_tail(board); // TODO: Add option to have multiple pieces gained per apple

    PRINT_HEAD(board->boardWin, board->snakeParts);
}

void place_head(Board *board) {
    uint16_t y;
    uint16_t x;
    next_head(board->snakeParts, &y, &x, board->currentDirection);
    add_piece(board->snakeParts, y, x);
}


void trunc_tail(Board *board) {
    Graphic tailPiece;
    if(deque(board->snakeParts, &tailPiece)) {
        endwin();
        fprintf(stderr, "ERROR: Attempted to deque empty queue\n");
        exit(1);
    }
    mvwaddch(board->boardWin, tailPiece.y, tailPiece.x, ' ');
}

void end_round(Board *board) {
    clear_win(board->boardWin);

    Graphic tailPiece;
    while(deque(board->snakeParts, &tailPiece));
    free(board->apple);
    end_prompt(board);
}