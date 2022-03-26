#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "useful.h"

int check(int x) {
	if (x < 0) {
		x *= -1;
	}
	int prev = 0, cur = 10;
	while (x > 0) {
		prev = cur;
		cur = x % 10;
		x /= 10;
		if (cur > prev) {
			return 0;
		}
	}
	return 1;
}

int *workline(int *newsize, int *line, int size) {
	int i = 0, *ans = (int) malloc(size * sizeof(int)), *ptr = line, amount = 0;
	for (i = 1; i <= size; i++) {
		if(check(*ptr)) {
			amount++;
			ans[amount-1] = *ptr;
		}
		ptr++;
	}
	ans = (int*) realloc(ans, amount * sizeof(int));
	*newsize = amount;
	return ans;
}

int **work(int **mat, int amount, int *strsizes, int **newss) {
	int **newmat = (int**) malloc(amount * sizeof(int*)), *newstrsizes = (int*) malloc(amount * sizeof(int));
	int i = 0, **newptr = newmat, *newptrs = newstrsizes, **ptr = mat, *ptrs = strsizes;
	for (i = 1; i <= amount; i++) {
		*newptr = workline(newptrs, *ptr, *ptrs);
		if (!(*newptr)){
			printf("%dth line is empty. Clearing matrix and shutting down the program.", i);
			clear(newmat, i-1, newstrsizes);
			return NULL;
		}
		newptrs++;
		newptr++;
		ptrs++;
		ptr++;
	}
	*newss = newstrsizes;
	return newmat;
}
