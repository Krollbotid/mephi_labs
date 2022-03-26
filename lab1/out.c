#include <stdio.h>
#include <stdlib.h>

void output(int **mat, int amount, int *strsizes) {
    int i = 0, **ptr = mat, *ptrs = strsizes;
    for (i = 1; i <= amount; i++) {
        int *ptrc = *ptr, j = 0;
        for (j = 1; j <= *ptrs; j++) {
            printf("%d ", *ptrc);
            ptrc++;
        }
        printf("\n");
        ptrs++;
        ptr++;
    }
    return;
}
