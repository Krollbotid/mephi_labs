#include <stdlib.h>
#include "ind.h"

int qpush(queue *dst, int data) {
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
        free(ptr_prev);
    } while (ptr != src->last);
    return;
}

int getfirst(queue *src) {
    if (src->last) {
        return src->last->next->data;
    }
    return 0;
}

int ExtractMin(queue *src, double *d) {
    if(!(src->last)) {
        return -1;
    }
    item *ptr = src->last->next, *prev = src->last, *del = ptr, *delprev = prev;
    int ans = ptr->data;
    double mind = d[ptr->data];
    do {
        if (d[ptr->data] < mind) {
            mind = d[ptr->data];
            ans = ptr->data;
            del = ptr;
            delprev = prev;
        }
        prev = ptr;
        ptr = ptr->next;
    } while (ptr != src->last->next);
    if (del == src->last) {
        src->last = NULL;
        ans = ptr->data;
        free(ptr);
        return ans;
    }
    delprev->next = del->next;
    free(del);
    return ans;
}