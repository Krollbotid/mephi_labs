#ifndef TABLE_H
#define TABLE_H

#include "ks1.h"
#include "ks2.h"

typedef int IndexType2;
typedef struct Table {
	KeySpace1 *ks1;
	KeySpace2 *ks2;
    IndexType2 msize2;
} Table;

int tabInit(Table *ans, int msize2);
int tabInsert(Table *table, KeyType1 par, Item *info);
int tabClear(Table *table);
int tabRemove(Table *table, KeyType1 key1, KeyType2 key2, int mode);
int tabPrint(Table *table);
int tabSearch(Table *table, KeyType1 key1, KeyType2 key2);
int tabSearchAny(Table *table, KeyType1 key1, KeyType2 key2, int mode);
int parSearch(Table *table, KeyType1 par);
int multRemove(Table *table, KeyType1 key1);

#endif
