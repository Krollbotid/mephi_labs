#ifndef LIST_H
#define LIST_H

typedef struct item {
    client data;
    item *next;
} item;
typedef struct list {
    item *head;
    item *tail;
} list;

#endif