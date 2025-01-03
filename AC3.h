#define MAX_VARS 100
#define MAX_DOMAIN 100
#define MAX_CONSTRAINT_VARS 10

typedef struct {
    int var1;
    int var2;
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