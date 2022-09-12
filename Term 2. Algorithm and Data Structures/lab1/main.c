#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "in.h"
#include "out.h"
#include "work.h"
#include "useful.h"

int main() {
    int amount = 0, *strsizes = NULL, **mat = input(&amount, &strsizes);
    if (!mat) {
        return 0;
    }
    printf("Printing your matrix.\n");
    output(mat, amount, strsizes);
    printf("Printing new matrix.\n");
    int *newstrsizes = NULL, **newmat = work(mat, amount, strsizes, &newstrsizes);
    clear(mat, amount, strsizes);
    if (!newmat) {
	return 0;
    }
    output(newmat, amount, newstrsizes);
    clear(newmat, amount, newstrsizes);
    return 0;
}
