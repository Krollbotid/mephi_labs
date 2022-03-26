#include <string.h>
#include <stdlib.h>
#include <string.h>

void clear(int **mat, int amount, int *sizes) {
    if (!mat || !sizes) {
        return;
    }
    int i = 0, **ptr = mat;
    for (; i < amount; i++) {
        free(*ptr);
        ptr++;
    }
    free(mat);
    free(sizes);
    return;
}