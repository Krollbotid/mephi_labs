#ifndef TREE_H
#define TREE_H

#include "useful.h"

#define RED 0
#define BLACK 1

typedef char KeyType;
typedef char Info;
typedef struct Node {
	KeyType *key;
	struct Node *left,
		*right,
		*par;
	int color;  // 0 - red
	Info *info;
} Node;

typedef struct Tree {
	struct Node *root,
		*EList;
} Tree;

Tree TreeInit();
void ClearTREE(Tree *tree);
int NodeDelete(Node *node);
int RB_Insert(Tree *tree, Node *node);
int TreeDelete(Tree *tree, KeyType *key);
int TreeGoAround(Tree *tree, KeyType *key);
int TreeClear(Tree *tree);
Node **TreeSearch(Tree *tree, KeyType *key, int *size, int *errcode);
int PrintNode(Node *node);
Node **TreeSpecialSearch (Tree *tree, KeyType *key, int *size, int *errcode);
int PrintTree(Tree *tree);
int ReadTreefromFile(Tree *tree, char *name);
int WriteTreeforGraph(Tree *tree);
int WriteTreetoFile(Tree *tree, char *name);

#endif
