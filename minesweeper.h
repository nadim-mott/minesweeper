#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define BOMB_CHAR '*'
#define FLAG_CHAR 'F'
#define NOT_REVEALED_CHAR '#'
#define CELL_MINE -1


typedef enum status{lost, ongoing, won} Status;

typedef enum cell{flag, shown, not_shown} Cell;

typedef struct board {
    int rows;
    int cols;
    int* cells;
} Board;

typedef struct game {
    Board board;
    int num_mines;
    int num_mines_found;
    int num_mines_guessed;
    Cell* revealed;
    Status status;
} Game;

int board_get_index(Board board, int row, int col);

char val_at_cell(Board board, int row, int col);

Cell reveal_at_cell(Game game, int row, int col);

Game create_game(Board board, int rows, int cols, int num_mines);

Board generate_random_board(int rows, int cols, int num_mines);

Board generate_random_board_with_safe_space(int rows, int cols, int num_mines, int starting_row, int starting_col);

int reveal(Game* game, int row, int col);

void flag_cell(Game* game, int row, int col);