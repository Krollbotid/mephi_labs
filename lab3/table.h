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

#endif
