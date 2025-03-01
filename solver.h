#include "minesweeper.h"
#include "AC3.h"
#include <stdlib.h>

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

void free_solver(Solver* s);

void solve_game(Solver* s);