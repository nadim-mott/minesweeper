#include "utils.h"
#include <stdlib.h>

void FisherYates(int* sequence, int size, int n){
    // shuffle the first elements of the sequence
    for (int i = 0; i < n; i++){
        int j = i + random() % (size - i);
        int temp = sequence[i];
        sequence[i] = sequence[j];
        sequence[j] = temp;
    }
}