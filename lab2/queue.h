#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue {
} queue;

void *newqueue(int size);
void *newqueue(int size);
void clear(queue *qu, int size);
void inqueue(queue *qu, int n, client cur);
void outqueue(queue *qu, int size, int tcur, int *tend);
void printqueue(queue *qu, int size);

#endif