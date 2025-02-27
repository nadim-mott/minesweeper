#include "minesweeper.h"
#include "AC3.h"

typedef struct {
    game game;
    Domain* domains;
    Constraint* constraints;
    int numVars;
    int numConstraints;

} solver;

void scan_game(solver* s){
    /// Scans the game state
    for (int row = 0; row < s->game.board.rows; row++){
        for (int col = 0; col < s->game.board.cols; col++){
            
        }
    }
}