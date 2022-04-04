#ifndef DTABLE_H
#define DTABLE_H

#include "table.h"

int dinsert(Table *table);
int dremove(Table *table);
int menu(int *id);
int errprint(int errcode);

#endif
