#ifndef ITEM_H
#define ITEM_H

typedef struct InfoType {
	int tbegin;
	int tend;
	int count;
	float divided;
} InfoType;

typedef int RelType;
typedef float KeyType1;
typedef int KeyType2;

typedef struct Item {
	InfoType *info;
	RelType release;
	Item *next;
	KeyType1 key1;
	KeyType2 key2;
} Item;

int ItemClear(Item *whom);
int ItemReleaseFixer(Item *first);
int ItemReleaseInsert(Item *first, Item *newitem);

#endif
