#ifndef KS2_H
#define KS2_H

#include "item.h"

typedef struct KeySpace2 {
	KeyType2 key;
	Item *info;
	KeySpace2 *next;
} KeySpace2;

int ks2ArrCreate(int msize2, KeySpace2 **ans);
int ks2Clear(KeySpace2 *src, int msize2, int mode);

#endif
