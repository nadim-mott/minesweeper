#include <stdio.h>
#include <stdlib.h>
#include "AC3.h"


int isConsistent(int values[], int numVars) {
    // Example constraint: variables must have different values
    for (int i = 0; i < numVars - 1; i++) {
        for (int j = i + 1; j < numVars; j++) {
            if (values[i] == values[j]) {
                return 0; 
            }
        }
    }
    return 1;
}

void initializeQueue(Arc queue[], int *queueSize, int numVars) {
    *queueSize = 0;
    for (int i = 0; i < numVars; i++) {
        for (int j = 0; j < numVars; j++) {
            if (i != j) {
                queue[(*queueSize)++] = (Arc){i, j};
            }
        }
    }
}

int revise(Domain domains[], Arc arc, Constraint constraints[], int numConstraints) {
    int revised = 0;
    for (int i = 0; i < domains[arc.var1].size; i++) {
        int x = domains[arc.var1].domain[i];
        int consistent = 0;
        for (int j = 0; j < domains[arc.var2].size; j++) {
            int y = domains[arc.var2].domain[j];
            for (int k = 0; k < numConstraints; k++) {
                int values[MAX_CONSTRAINT_VARS];
                int foundVar1 = 0, foundVar2 = 0;
                for (int l = 0; l < constraints[k].numVars; l++) {
                    if (constraints[k].vars[l] == arc.var1) {
                        values[l] = x;
                        foundVar1 = 1;
                    } else if (constraints[k].vars[l] == arc.var2) {
                        values[l] = y;
                        foundVar2 = 1;
                    } else {
                        values[l] = domains[constraints[k].vars[l]].domain[0]; // Assume first value for other variables
                    }
                }
                if (foundVar1 && foundVar2 && constraints[k].constraint(values, constraints[k].numVars)) {
                    consistent = 1;
                    break;
                }
            }
            if (consistent) break;
        }
        if (!consistent) {
            for (int k = i; k < domains[arc.var1].size - 1; k++) {
                domains[arc.var1].domain[k] = domains[arc.var1].domain[k + 1];
            }
            domains[arc.var1].size--;
            i--;
            revised = 1;
        }
    }
    return revised;
}

int AC3(Domain domains[], int numVars, Constraint constraints[], int numConstraints) {
    /// Run AC3 Algorithm, returns 1 if consistent, 0 if inconsistent, revise all the domains appropriately     
    Arc queue[MAX_VARS * MAX_VARS];
    int queueSize;
    initializeQueue(queue, &queueSize, numVars);

    while (queueSize > 0) {
        Arc arc = queue[--queueSize];
        if (revise(domains, arc, constraints, numConstraints)) {
            if (domains[arc.var1].size == 0) {
                return 0; // Inconsistent
            }
            for (int i = 0; i < numVars; i++) {
                if (i != arc.var1) {
                    queue[queueSize++] = (Arc){i, arc.var1};
                }
            }
        }
    }
    return 1; // Consistent
}

int test_AC3() {
    Domain domains[MAX_VARS];
    Constraint constraints[MAX_VARS * MAX_VARS];
    int numVars = 3;
    int numConstraints = 1;

    // Initialize domains
    for (int i = 0; i < numVars; i++) {
        domains[i].size = 3;
        for (int j = 0; j < 3; j++) {
            domains[i].domain[j] = j + 1;
        }
    }

    // Initialize constraints
    constraints[0].numVars = 2;
    constraints[0].vars[0] = 0;
    constraints[0].vars[1] = 1;
    constraints[0].constraint = isConsistent;

    if (AC3(domains, numVars, constraints, numConstraints)) {
        printf("Consistent\n");
    } else {
        printf("Inconsistent\n");
    }

    return 0;
}