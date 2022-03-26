#include <stdio.h>
#include <stdlib.h>
#include "libra.h"

int qpush(queue *dst, client toadd) {
    if (dst->amount < dst->size) {
        client *ptr = dst->arr;
        ptr[dst->tail] = toadd;
        dst->tail = (dst->tail + 1) % dst->size;
        dst->amount = dst->amount + 1;
        return 0;
    }
    return 1;
}

int qpop(queue *src) {
    if (src->amount > 0) {
	    client *ptr = src->arr + src->head;
	    free(ptr->id);
        ptr->id = NULL;
        src->head = (src->head + 1) % src->size;
        src->amount = src->amount - 1;
        return 0;
    }
    return 1;
}

queue newqueue(int size) {
    queue nov;
    nov.arr = (client*) calloc(size, sizeof(client));
    nov.amount = 0;
    nov.head = 0;
    nov.tail = 0;
    nov.size = size;
    return nov;
}

void delqueue(queue *src) {
    int i = 0;
    client *ptr = src->arr;
    for (; i < src->size; i++) {
        free(ptr->id);
        ptr->id = NULL;
        ptr++;
    }
    free(src->arr);
    src->arr = NULL;
    return;
}

client *getfirst(queue *src) {
    if (src->amount) {
        client *ptr = src->arr;
        return ptr + src->head;
    }
    return NULL;
}

int fullcheck(queue *src) {
    return src->amount < src->size;
}

void printqueue(queue *src, int n) {
    queue *ptr = src;
    int i = 0, j = 0;
    for (; i < n; i++) {
        printf("\n#%d", i + 1);
        client *src2 = ptr->arr;
        for (j = 0; j < ptr->amount; j++) {
            printf(" %s", (src2[(j + ptr->head) % ptr->size]).id);
        }
        ptr++;
    }
}
