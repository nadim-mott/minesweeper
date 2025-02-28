#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "minesweeper.h"
#include "utils.h"



int board_get_index(Board board, int row, int col){
    /// Returns the index of the cell at the given row and column
    return row * board.cols + col;
}

char val_at_cell(Board board, int row, int col){
    /// Returns the value at the cell at the given row and column
    int num_cols = board.cols;
    int index = row * num_cols + col;
    return board.cells[index];
}

Cell reveal_at_cell(Game game, int row, int col){
    /// Reveals the cell at the given row and column
    int index = board_get_index(game.board, row, col);
    return game.revealed[index];
}

void add_mine(Board board, int row, int col){
    /// Adds a mine to the board at the given row and column
    int num_rows = board.rows;
    int num_cols = board.cols;
    int index = board_get_index(board, row, col);
    board.cells[index] = CELL_MINE;
    for (int r = max(0, row - 1); r <= min(num_rows - 1, row + 1);r ++){
        for (int c = max(0, col - 1); c <= min(num_cols - 1, col + 1); c++){
            if (val_at_cell(board, r, c) != CELL_MINE){
                board.cells[board_get_index(board, r, c)]++;
            }
        }
    }
}

Board generate_random_board(int rows, int cols, int num_mines){
    /// Generates a board with the given number of rows and columns and the given number of mines
    /// If the number of mines is greater than the possible number of mines generate with all mines

    // Allocate space to the cells
    int* cells = malloc(rows * cols * sizeof(int));
    if (!cells){
        fprintf(stderr, "Error: Could not allocate memory for cells\n");
        exit(1);
    }
    Board board = {rows, cols, cells};

    // Verify that there aren't more mines than there are cells
    if (num_mines > rows * cols){
        num_mines = rows * cols;
    }

    // Initialize all cells to have no mines adjacent
    for (int i = 0; i < rows * cols; i++){
        cells[i] = 0;
    }

    for(int i = 0; i < num_mines; i++){
        int index = 0;
        int row = 0;
        int col = 0;
        do {
            row = random() % rows;
            col = random() % cols;
            index = row * cols + col;
        } while (cells[index] == CELL_MINE);
        add_mine(board, row, col);
    }
    return board;
}

Board generate_random_board_with_safe_space(int rows, int cols, int num_mines, int starting_row, int starting_col){
    // Generates a board with the given number of rows and columns and the given number of mines
    // If the number of mines is greater than the possible number of mines generate with all mines
    // The column and row of the starting cell are guaranteed to be safe as well as the spots around 

    // Allocate space to the cells
    int* cells = malloc(rows * cols * sizeof(int));
    if (!cells){
        fprintf(stderr, "Error: Could not allocate memory for cells\n");
        exit(1);
    }
    Board board = {rows, cols, cells};
    if (num_mines > rows * cols - 9){
        num_mines = rows * cols - 9;
    }

    int safe_start_1 = board_get_index(board, max(0, starting_row - 1), max(0,starting_col - 1));
    int safe_start_2 = board_get_index(board, starting_row, max(0,starting_col - 1));
    int safe_start_3 = board_get_index(board, min(starting_row + 1, board.rows - 1), max(0,starting_col - 1));
    int num_cols_safe = starting_col == 0 || starting_col == board.cols - 1 ? 2 : 3;
    int num_rows_safe = starting_row == 0 || starting_row == board.rows - 1 ? 2 : 3;

    int* spots = malloc((rows * cols * sizeof(int)) - (num_cols_safe * num_rows_safe));
    if (!spots){
        fprintf(stderr, "Error: Could not allocate memory for spots\n");
        exit(1);
    }
    int spot_index = 0;
    for (int i = 0; i < rows * cols; i = i){
        if (i == safe_start_1 || i == safe_start_2 || i == safe_start_3){
            i += num_cols_safe;
        } else {
            spots[spot_index] = i;
            // for debugging:
            //cells[i] = 5;
            spot_index += 1;
            i++;
        }
    }
    FisherYates(spots, rows * cols - num_cols_safe * num_rows_safe, num_mines);
    for (int i = 0; i < num_mines; i++){
        add_mine(board, spots[i] / board.cols, spots[i] % board.cols);
    }
    free(spots);
    return board;
}




Game create_game(Board board, int rows, int cols, int num_mines){
    /// Creates a game with the given number of rows and columns and the given number of mines
    // Initialize random number generator:

    // Initialize revealed map
    Cell* revealed = malloc(rows * cols * sizeof(int));
    if (!revealed){
        fprintf(stderr, "Error: Could not allocate memory for revealed\n");
        exit(1);
    }

    // Initialize the revealed map so nothing is revealed.
    for (int i = 0; i < rows * cols; i++){
        revealed[i] = not_shown;
    }
    Game game = {board, num_mines, 0, 0, revealed, ongoing};
    return game;
}

int reveal(Game* game, int row, int col){
    /// Reveals the cell at the given row and column
    int index = board_get_index(game->board, row, col);
    if (reveal_at_cell(*game, row, col) != not_shown){
        return val_at_cell(game->board, row, col);
    }
    game->revealed[index] = shown;
    int cell_value = val_at_cell(game->board, row, col);
    
    if (cell_value == CELL_MINE){
        game->status = lost;
    } else if (cell_value == 0){
        for (int r = max(0, row - 1); r <= min(game->board.rows - 1, row + 1); r++){
            for (int c = max(0, col - 1); c <= min(game->board.cols - 1, col + 1); c++){
                reveal(game, r, c);
            }
        }
    }
    return cell_value;
}



void flag_cell(Game* game, int row, int col){
    /// Flags the cell at the given row and column
    int index = board_get_index(game->board, row, col);
    if (game->revealed[index] == shown){
        return;
    }
    if (game->revealed[index] == flag){
        game->num_mines_guessed --;
        game->revealed[index] = not_shown;
        if (game->board.cells[index] == CELL_MINE){
            game->num_mines_found--;
        }
    } else if (game->revealed[index] == not_shown) {
        game->num_mines_guessed ++;
        game->revealed[index] = flag;
        if (game->board.cells[index] == CELL_MINE){
            game->num_mines_found++;
        }
    }
    if (game->num_mines_found == game->num_mines){
        game->status = won;
    }
    return;
}

void free_game(Game game){
    /// Frees the game
    free(game.board.cells);
    free(game.revealed);
}