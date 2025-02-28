#include "solver.h"



solver* create_solver(Game* game){
    Board board = game->board;
    solver* solver = malloc(sizeof(solver));
    solver->domains = malloc(sizeof(Domain) * board.cols * board.rows);
    solver->constraints = malloc(1);
    solver->numVars = board.cols * board.rows;
    solver->numConstraints = 0;
    scan_game(solver);

}


void scan_game(solver* s){
    // Scans the current state of the board
    // Precondition: s is initialized
    Game* game = s->game;
    Board board = game->board;
    Domain* cell_domains = s->domains;
    
    for (int row = 0; row < board.rows; row ++){
        for (int col = 0; col < board.cols; col ++){
            int cell_index = board_get_index(board, row, col);
            Domain dom = {
                .domain = {0, 1},
                .size = 2
            };
            if (reveal_at_cell(*game, row, col) == shown){
                dom.domain = {0};
            }
        }
    }
}