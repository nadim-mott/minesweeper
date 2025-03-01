#define MAX_VARS (26 * 26)
#define MAX_DOMAIN 2
#define MAX_CONSTRAINT_VARS 9

typedef struct {
    int vars[MAX_CONSTRAINT_VARS];
    int numVars;
} Arc;

typedef struct {
    int domain[MAX_DOMAIN];
    int size;
} Domain;

typedef struct {
    int vars[MAX_CONSTRAINT_VARS];
    int numVars;
    int (*constraint)(int[], int);
} Constraint;  

int AC3(Domain domains[], int numVars, Constraint constraints[], int numConstraints);