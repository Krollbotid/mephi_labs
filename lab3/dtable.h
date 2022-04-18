#ifndef DTABLE_H
#define DTABLE_H

#include "table.h"

int getsizeofks2(int *size);
int dInsert(Table *table);
int dRemove(Table *table);
int menu(int *id);
char **errarray();
int errprint(int errcode, char **arr);
int dSearch(Table *table);
int dSearchAny(Table *table);
int dRemoveAny(Table *table);
int dparSearch(Table *table);
int dmultRemove(Table *table);

#endif
