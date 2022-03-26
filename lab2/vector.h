#ifndef VECTOR_H
#define VECTOR_H
#include "libra.h"

#define QU_SIZE 80
typedef struct vector {
    client arr[QU_SIZE];
    int head;
    int tail;
    int amount;
} vector;

void *newqueue(int size);
void clear(void *queue, int size);
void inqueue(void *queue, int n, client cur);
void outqueue(void *queue, int size, int tcur);
void printqueue(void *queue, int size);

#endif
