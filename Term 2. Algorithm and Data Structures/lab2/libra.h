#ifndef LIBRA_H
#define LIBRA_H


typedef struct client {
    char *id;
    int ta;
    int ts;
} client;

int readclient(client *dest, int *tend);
int scalerand(const int start, const int end);

#ifdef USEVECTOR
typedef struct queue {
    client *arr;
    int head;
    int tail;
    int amount;
    int size;
} queue;
#else
typedef struct item {
    client data;
    struct item *next;
} item;

typedef struct queue {
    item *last;
} queue;
#endif

int qpush(queue *dst, client toadd);
int qpop(queue *src);
queue newqueue(int size);
void delqueue(queue *src);
client *getfirst(queue *src);
int fullcheck(queue *src);
void printqueue(queue *src, int n);

queue *qarr(int n);
void clear(queue *arr, int n);
void outqueue(queue *arr, int n, int tcur, int *tend);
void inqueue(queue *dst, int n, client cur);

#endif