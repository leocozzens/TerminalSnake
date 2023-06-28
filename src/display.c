#include <display.h>

void set_win(Board *board) {
    // Ncurses init
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    size_t maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    board->height = BOARD_SCALE; // TODO: Add scaling default, and custom size determined by switch, ensure overflow protection
    board->width = board->height * 2.5;

    if(board->height > maxY || board->width > maxX) {
        board->height = maxY - SCOREBOARD_HEIGHT;
        board->width = board->height * 2.5;
        if(board->width > maxX || maxY < (START_LENGTH + 2 + SCOREBOARD_HEIGHT)) { // Added 4 to allow for both borders and one block of space
            endwin();
            fprintf(stderr, "ERROR: Terminal size too small");
            exit(1);
        }
    }

    int middleX = (maxX - board->width) / 2;
    board->boardWin = newwin(board->height, board->width, (maxY - board->height - SCOREBOARD_HEIGHT)/2, middleX); //TODO: position from bottom if terminal size triggered resize has occured

    int scoreBoardY, scoreBoardX;
    getbegyx(board->boardWin, scoreBoardY, scoreBoardX);

    scoreBoardY = scoreBoardY + board->height - SCOREBOARD_HEIGHT/2;

    board->scoreBoard = newwin(SCOREBOARD_HEIGHT, board->width, scoreBoardY, middleX);

    keypad(board->boardWin, 1);
    refresh();
}

void clear_win(WINDOW *boardWin) {
    wclear(boardWin);
    SET_BORDER(boardWin);
    wrefresh(boardWin);
}

void clear_score(WINDOW *scoreBoard) {
    wclear(scoreBoard);
    SET_BORDER_ROOFLESS(scoreBoard, 0);
    mvwprintw(scoreBoard, 1, SCOREBOARD_HEIGHT/2, "SCORE:");
    wrefresh(scoreBoard);
}

void get_empty_locale(Board *board, uint16_t *y, uint16_t *x) { // TODO: Add counter to check if board is full
    do {
        *y = rand() % (board->height - 1);
        *x = rand() % (board->width - 1);
    } while(mvwinch(board->boardWin, *y, *x) != ' ');
}

void print_snake(Board *board) {
    SnakePiece *tmp = board->snakeParts->tail;
    while(tmp != NULL) {
        mvwaddch(board->boardWin, tmp->piece.y, tmp->piece.x, SNAKE_ICON);
        tmp = tmp->nextPiece;
    }
}

void update_score(Board *board) {
    char scoreStr[board->width];

    snprintf(scoreStr, board->width, "%" PRIu64, board->score); // TODO: Add statement to check if score has filled bar
    mvwprintw(board->scoreBoard, SCOREBOARD_HEIGHT/2, board->width - strlen(scoreStr) - 1, scoreStr);
    wrefresh(board->scoreBoard);
}

void end_prompt(Board *board) {
    printw("%lu ", board->score);
    getch();
}