#ifndef IND_H
#define IND_H

typedef struct item {
    int data;
    struct item *next;
} item;

typedef struct queue {
    item *last;
} queue;

int qpush(queue *dst, int toadd);
int qpop(queue *src);
queue newqueue(int size);
void delqueue(queue *src);
int getfirst(queue *src);
int ExtractMin(queue *src, double *d);

#endif