#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libra.h"
#define BFSZ 80

char *readid() {
    scanf("*c");
	char buf[BFSZ + 1] = {0};
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = scanf("%80[^/\n]", buf);
		if (n < 0) {
			if (!ans) {
				return NULL;
			}
		} else if (n > 0) {
			int buf_len = strlen(buf);
			int str_len = len + buf_len;
			ans = (char*) realloc (ans, (str_len + 1) * sizeof(char));
			strncpy(ans + len, buf, buf_len);
			len = str_len;
		}
	} while (n > 0);
	if (len > 0) {
		ans[len]='\0';
	}
	return ans;
}

int readclient(client *dest, int *tend) {
    client cur;
    cur.id = readid();
    if (!(cur.id)) {
        dest->id = NULL;
        dest->ta = -1;
        dest->ts = -1;
        return 1;
    }
    if (scanf("/%d/%d", &(cur.ta), &(cur.ts)) < 2) {
        printf("\nIncorrect input of %s's data\n", cur.id);
        free(cur.id);
        dest->id = NULL;
        dest->ta = -1;
        dest->ts = -1;
        return 1;
    }
    if ((cur.ts < 1) || (cur.ta < 1)) {
        printf("\nIncorrect input of %s's data\n", cur.id);
        free(cur.id);
        dest->id = NULL;
        dest->ta = -1;
        dest->ts = -1;
        return 1;
    }
    *dest = cur;
    if (*tend < cur.ta + cur.ts) {
        *tend = cur.ta + cur.ts;
    }
    return 0;
}

int scalerand(const int start, const int end) {
    if (end > start){
        return start + (rand() % (end - start));
    } else {
        return end - 1;
    }
}

queue *qarr(int n) {
    queue *arr = (queue*) malloc(n * sizeof(queue)), *ptr = arr;
    int i = 0;
    for (; i < n; i++) {
        *ptr = newqueue(3);
        ptr++;
    }
    return arr;
}

void clear(queue *arr, int n) {
    queue *ptr = arr;
    int i = 0;
    for (; i < n; i++) {
        delqueue(ptr);
        ptr++;
    }
    free(arr);
    return;
}

void outqueue(queue *arr, int n, int tcur, int *tend) {
    if (!tcur) {
        return;
    }
    int i = 0;
    queue *ptr = arr;
    for (; i < n; i++) {
        client *cur = getfirst(ptr);
        if (cur) {
            if (cur->ta + cur->ts == tcur) {
                qpop(ptr);
                cur = getfirst(ptr);
                if(cur) {
                    cur->ta = tcur;
                    if (*tend < tcur + cur->ts) {
                        *tend = tcur + cur->ts;
                    }
                }
                printf("\nCurrent time:%d", tcur);
                printqueue(arr, n);
            }
        }
        ptr++;
    }
    return;
}

void inqueue(queue *dst, int n, client cur) {
    int i = 0, *arr = (int*) malloc(n * sizeof(int)), *ptr = arr, count = 0;
    queue *ptr2 = dst;
    for (; i < n; i++) {
        if (fullcheck(ptr2)){
            *ptr = i;
            ptr++;
            count++;
        }
        ptr2++;
    }
    if (count > 0) {
        qpush(dst + arr[scalerand(0, count)], cur);
    } else {
        printf("All queues are full, client left!\n");
        free(cur.id);
    }
    free(arr);
    return;
}