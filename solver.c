#include "solver.h"



Solver* create_solver(Game* game){
    Board board = game->board;
    Solver* solver = malloc(sizeof(solver));
    solver->domains = malloc(sizeof(Domain) * board.cols * board.rows);
    solver->constraints = malloc(sizeof(Constraint) * board.cols * board.rows);
    solver->numVars = board.cols * board.rows;
    solver->numConstraints = 0;
    scan_game(solver);

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
                char cell_val = val_at_cell(game->board, row, col);
            }
        }
    }
}

void add_constraint(Solver* s, Constraint constraint){
    s->constraints[s->numConstraints] = constraint;
    s->numConstraints ++;

}