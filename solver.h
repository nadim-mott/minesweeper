#include "minesweeper.h"
#include "AC3.h"

typedef struct {
    Game* game;
    Domain* domains;
    Constraint* constraints;
    int numVars;
    int numConstraints;
} solver;

solver* create_solver(Game* game);

void scan_game(solver* s);

void add_constraint(solver* s, Constraint constraint);