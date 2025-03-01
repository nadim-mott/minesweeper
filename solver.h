#include "minesweeper.h"
#include "AC3.h"

typedef struct {
    Game* game;
    Domain* domains;
    Constraint* constraints;
    int numVars;
    int numConstraints;
} Solver;

Solver* create_solver(Game* game);

void scan_game(Solver* s);

void add_constraint(Solver* s, Constraint constraint);