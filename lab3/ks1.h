#ifndef KS1_H
#define KS1_H

#include "item.h"

typedef struct KeySpace1 {
	KeyType1 key;
	KeyType1 par;
	Item *info;
	struct KeySpace1 *next;
} KeySpace1;

int ks1InitCreate (KeySpace1 **where);
int ks1Clear(KeySpace1 *src, int mode);
int ks1Search(KeySpace1 *ks1, KeyType1 key, KeyType1 *par, Item **ans);
int ks1Insert(KeySpace1 *ks1, KeyType1 par, Item *info, Item **ans);
int ks1Remove(KeySpace1 **ks1, KeyType1 key, Item **ans, int mode);
int ks1Print(KeySpace1 *ks1);

#endif
