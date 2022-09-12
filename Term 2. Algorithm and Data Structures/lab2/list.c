#include <stdlib.h>
#include <stdio.h>
#include "libra.h"

int qpush(queue *dst, client data) {
    item *ptr = (item*) malloc(sizeof(item));
    if (!ptr) {
        return 1;
    }
    ptr->data = data;
    if (!(dst->last)){
        ptr->next = ptr;
    } else {
        ptr->next = dst->last->next;
        dst->last->next = ptr;
    }
    dst->last = ptr;
    return 0;
}

int qpop(queue *src) {
    if(!(src->last)) {
        return 1;
    }
    item *ptr = src->last->next;
    if (ptr == src->last){
        src->last = NULL;
    } else {
        src->last->next = ptr->next;
    }
    free((ptr->data).id);
    free(ptr);
    return 0;
}

queue newqueue(int size) {
    queue nov;
    nov.last = NULL;
    return nov;
}

void delqueue(queue *src) {
    if (!src) {
        return;
    }
    item *ptr = src->last, *ptr_prev;
    if (!ptr){
        return;
    }
    do {
        ptr_prev = ptr;
        ptr = ptr->next;
        free((ptr_prev->data).id);
        free(ptr_prev);
    } while (ptr != src->last);
    return;
}

client *getfirst(queue *src) {
    if (src->last) {
        return &(src->last->next->data);
    }
    return NULL;
}

int fullcheck(queue *src) {
    return 1;
}

void printqueue(queue *src, int n) {
    queue *ptr = src;
    int i = 0, j = 0;
    for (; i < n; i++) {
        printf("\n#%d", i + 1);
        item *ptr2 = ptr->last;
        if (ptr2) {
            ptr2 = ptr2->next;
            do {
                printf(" %s", (ptr2->data).id);
                ptr2 = ptr2->next;
            } while (ptr2 != ptr->last->next);
        }
        ptr++;
    }
}