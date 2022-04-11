#ifndef DTABLE_H
#define DTABLE_H

#include "table.h"

int dInsert(Table *table);
int dRemove(Table *table);
int menu(int *id);
int errprint(int errcode);
int tabPrint(Table *table);

#endif
