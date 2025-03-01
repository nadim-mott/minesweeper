#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "solver.h"

char* board_to_string(Board board){
    /// Converts the board to a string
    char* str = malloc(board.rows * board.cols * sizeof(char));
    if (!str){
        fprintf(stderr, "Error: Could not allocate memory for string\n");
        exit(1);
    }
    for (int i = 0; i < board.rows * board.cols; i++){
        if (board.cells[i] == -1){
            str[i] = BOMB_CHAR;
        } else {
            str[i] = board.cells[i] + '0';
        }
    }
    return str;
}
char char_at_cell(Game game, int row, int col){
    /// Returns the character at the given cell
    if (reveal_at_cell(game, row, col) == flag){
        return FLAG_CHAR;
        
    } else if (reveal_at_cell(game, row, col) == shown || game.status != ongoing){
        if (val_at_cell(game.board, row, col) == -1){
            return BOMB_CHAR;
        }
        return val_at_cell(game.board, row, col) + '0';
    } else {
        return NOT_REVEALED_CHAR;
    }
}

void print_game_state(Game game){
    /// Converts the game to a string
    Board board = game.board;

    // Check if the board is too large (ensures that each column coord is a single character)
    if (board.cols > 26){
        fprintf(stderr, "Error: Games with over 26 columns unsupported\n");
        exit(1);
    }

    // Display the number of mines left or the win/ lost condition
    if (game.status == lost){
        printf("You lost!\n ");
    } else if (game.status == won){
        printf("You won!\n ");
    } else {
        printf("Mines: %d/%d\n ", game.num_mines_guessed, game.num_mines);
    }
    // Add spaces so that the coordinates line up with the columns
    int log_10_rows = (board.rows == 0) ? 1 : log10(board.rows - 1) + 1;
    for (int i = 0; i < log_10_rows; i++){
        printf(" ");
    }

    // Print the column coordinates
    for (char c = 'A'; c < 'A' + board.cols; c++){
        printf("%c", c);
    }
    printf("\n");
    for (int row = 0; row < board.rows; row++){
        int number_of_digits_in_row_number = (row == 0) ? 1 : log10(row) + 1;
        int num_zero = log_10_rows - number_of_digits_in_row_number;
        for (int i = 0; i < num_zero; i++){
            printf("0");
        }
        printf("%d ", row);
        for (int col = 0; col < board.cols; col++){
            printf("%c", char_at_cell(game, row, col));
        }
        printf("\n");
    }
}

int letter_to_column(char c){
    /// Converts a letter to a column number
    return c - 'A';
}


int main(int argc, char** argv){
    /// Main function
    if (argc != 4){
        fprintf(stderr, "Usage: %s <rows> <cols> <num_mines>\n", argv[0]);
        exit(1);
    }
    srandom(time(NULL));

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int num_mines = atoi(argv[3]);

    int starting_row = random() % rows;
    int starting_col = random() % cols;

    Board board = generate_random_board_with_safe_space(rows, cols, num_mines, starting_row, starting_col);
    Game game = create_game(board, rows, cols, num_mines);
    Solver* solver = create_solver(&game);
    
    reveal(&game, starting_row, starting_col);
    while (game.status == ongoing){
        print_game_state(game);
        printf("Enter a command: ");
        char command;
        int row;
        char col_char;
        scanf("%c %d%c", &command, &row, &col_char);
        printf("%c %d%c\n", command, row, col_char);
        if (command == 'r'){
            reveal(&game, row, letter_to_column(col_char));
        } else if (command == 'f'){
            flag_cell(&game, row, letter_to_column(col_char));
        } else if (command == 'h') {
            scan_game(solver);
            solve_game(solver);
        } else {
            fprintf(stderr, "Invalid command [r,f] [row number] [col character]\n");
        }   
    }
    free_solver(solver);
    print_game_state(game);
    return 0;
}