#include "solver.h"



Solver* create_solver(Game* game){
    Board board = game->board;
    Solver* solver = malloc(sizeof(solver));
    solver->domains = malloc(sizeof(Domain) * board.cols * board.rows);
    solver->constraints = malloc(sizeof(Constraint) * board.cols * board.rows);
    solver->numVars = board.cols * board.rows;
    solver->numConstraints = 0;
    solver->game = game;
    scan_game(solver);
    return solver;
}

void free_solver(Solver* s){
    free(s->domains);
    free(s->constraints);
    free(s);
}
int cell_constraint_0(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 0;
}
int cell_constraint_1(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}
int cell_constraint_2(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}
int cell_constraint_3(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}

int cell_constraint_4(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}
int cell_constraint_5(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}
int cell_constraint_6(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}
int cell_constraint_7(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}
int cell_constraint_8(int* vars, int numVars) {
    // Constraint for a cell. The number of mines in the cell's neighborhood
    // must be equal to the cell's value
    int numMines = 0;
    for (int i = 0; i < numVars; i++) {
        if (vars[i] == 1) {
            numMines++;
        }
    }
    return numMines == 1;
}

Constraint create_cell_constraint(Board board, int row, int col){
    // Create constraint for cell at row, col. The number of mines
    // in the cell's neighborhood must be equal to the cell's value
    // Precondition: row and col are valid indices
    Constraint constraint;
    constraint.numVars = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < board.rows && newCol >= 0 && newCol < board.cols) {
                constraint.vars[constraint.numVars] = board_get_index(board, newRow, newCol);
                constraint.numVars++;
            }
        }
    }

    int cell_val = val_at_cell(board, row, col);
    switch (cell_val) {
        case 0:
            constraint.constraint = cell_constraint_0;
            break;
        case 1:
            constraint.constraint = cell_constraint_1;
            break;
        case 2:
            constraint.constraint = cell_constraint_2;
            break;
        case 3:
            constraint.constraint = cell_constraint_3;
            break;
        case 4:
            constraint.constraint = cell_constraint_4;
            break;
        case 5:
            constraint.constraint = cell_constraint_5;
            break;
        case 6:
            constraint.constraint = cell_constraint_6;
            break;
        case 7:
            constraint.constraint = cell_constraint_7;
            break;
        case 8:
            constraint.constraint = cell_constraint_8;
            break;
    }
    return constraint;
}

void scan_game(Solver* s){
    // Scans the current state of the board
    // Precondition: s is initialized
    Game* game = s->game;
    Board board = game->board;
    Domain* cell_domains = s->domains;
    
    for (int row = 0; row < board.rows; row ++){
        for (int col = 0; col < board.cols; col ++){
            int cell_index = board_get_index(board, row, col);
            Domain dom = {
                .size = 2
            };
            dom.domain[0] = 0;
            dom.domain[1] = 1;
            if (reveal_at_cell(*game, row, col) == shown){
                dom.size = 1;

            } else {
                add_constraint(s, create_cell_constraint(board, row, col));
            }
            cell_domains[cell_index] = dom;
        }
    }
}

void solve_game(Solver* s){
    // Solves the game
    // Precondition: s is initialized
    Game* game = s->game;
    Board board = game->board;
    Domain* cell_domains = s->domains;
    Constraint* constraints = s->constraints;
    int numVars = s->numVars;
    int numConstraints = s->numConstraints;

    AC3(cell_domains, numVars, constraints, numConstraints);

    for (int i = 0; i < numVars; i++){
        if (cell_domains[i].size == 1){
            int row = i / board.cols;
            int col = i % board.cols;
            if (cell_domains[i].domain[0] == 1){
                flag_cell(game, row, col);
            } else {
                reveal(game, row, col);
            }
        }
    }
}




void add_constraint(Solver* s, Constraint constraint){
    s->constraints[s->numConstraints] = constraint;
    s->numConstraints ++;

}






