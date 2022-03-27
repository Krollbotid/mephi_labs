#ifndef KS2_H
#define KS2_H

#include "item.h"

typedef struct KeySpace2 {
	KeyType2 key;
	Item *info;
	KeySpace2 *next;
} KeySpace2;

#endif
