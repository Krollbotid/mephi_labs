#ifndef KS1_H
#define KS1_H

#include "item.h"

typedef struct KeySpace1 {
	KeyType1 key;
	KeyType1 par;
	Item *info;
	KeySpace1 *next;
} KeySpace1;

int ks1InitCreate (KeySpace1 **where);
int ks1Clear(KeySpace1 *src, int mode);
int ks1Search(KeySpace1 *ks1, KeyType1 key, Item **ans);

#endif
