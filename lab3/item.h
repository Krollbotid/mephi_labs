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
typedef void PointerType1;

typedef struct Item {
	int info;
	RelType release;
	KeyType1 par;
	KeyType1 key1;
	KeyType2 key2;
	struct Item *next;
} Item;

int ItemDelete(Item *whom);
int ItemClear(Item *src);
int ItemReleaseFixer(Item *first);
int ItemReleaseInsert(Item *first, Item *newitem);
int ItemPrint(char *nameoffile, Item *first);

int fGetInfo(char *nameoffile, Item *item, InfoType *info);
int fInsertInfo(char *nameoffile, Item *item, InfoType *info);

#endif
