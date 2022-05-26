#ifndef TREE_H
#define TREE_H

#include "useful.h"

typedef char KeyType;
typedef char Info;
typedef struct Node {
	KeyType *key;
	struct Node *left,
		*right,
		*par;
	int color;  // 1 - red
	Info *info;
} Node;

int NodeDelete(Node *node);
int TreeInsert(Node **tree, Node *node);
int TreeDelete(Node **tree, KeyType *key);
int TreeGoAround(Node **tree);
int TreeClear(Node **tree);
Node **TreeSearch(Node *tree, KeyType *key, int *size, int *errcode);
int PrintNode(Node *node);
int TreeSpecialSearch (Node *tree, KeyType *key, Node **ans, int *size);
int PrintTree(Node **tree);
int ReadTreefromFile(Node **tree, char *name);
int WriteTreeforGraph(Node **tree);
int recReverseGo(Node *node);
int WriteTreetoFile(Node **tree, char *name);

#endif
