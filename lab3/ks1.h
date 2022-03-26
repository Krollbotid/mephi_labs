#ifndef KS1_H
#define KS1_H

#include "item.h"

typedef struct KeySpace1 {
	KeyType1 key;
	KeyType1 par;
	Item *info;
	KeySpace1 *next;
} KeySpace1;

#endif
