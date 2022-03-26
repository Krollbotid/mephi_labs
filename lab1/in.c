#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "useful.h"

int *inputline(int *size) {
	printf("Input new line:\n");
	int i = 0, n = 0, buf = 0;
	printf("Enter number of elements in line:");
	if (scanf("%d", &n) > 0) {
		int *ans = (int*) malloc(n * sizeof(int)), *ptr = ans;
		for (; i < n; i++) {
			if (scanf("%d", &buf) > 0) {
				*ptr = buf;
			} else {
				free(ans);
				return NULL;
			}
			ptr++;
		}
		*size = n;
		return ans;
	}
	return NULL;
}

int **input(int *amount, int **ss) {
	printf("Entering new matrix.\n");
	printf("Please enter amount of lines:");
	int m = 0;
	if (scanf("%d", &m) < 1) {
		printf("ENTERING IS WRONG!");
		return NULL;
	}
	printf("For entering each line you MUST follow next format:\n\"n a_1 a_2 ... a_n\", where n - amount of number in line, a_j - element of line with number j, 1<=j<=n\n");
	int **matrix = (int**) malloc(m * sizeof(int*)), *strsizes = (int*) malloc(m * sizeof(int));
	int i = 0, **ptr = matrix, *ptrs = strsizes;
	for (i = 1; i <= m; i++) {
		*ptr = inputline(ptrs);
		if (!(*ptr)){
			printf("Entering is wrong. Clearing matrix and shutting down the program.");
			clear(matrix, i-1, strsizes);
			return NULL;
		}
		ptrs++;
		ptr++;
	}
	*amount = m;
	*ss = strsizes;
	return matrix;
}
