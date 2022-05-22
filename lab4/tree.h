#ifndef TREE_H
#define TREE_H

typedef char KeyType;

typedef unsigned int Info;

typedef struct Node {
	KeyType *key;
	struct Node *left,
		*right,
		*par;
	Info info; // because it's stupid to store pointer on unsigned int instead unsigned int itself.
} Node;

int NodeDelete(Node *node);
int TreeInsert(Node **tree, Node *node, Info *info);
int TreeDelete(Node **tree, KeyType *key);
int TreeGoAround(Node **tree);
int TreeClear(Node **tree);
Node **TreeSearch(Node *tree, KeyType *key, int *size, int *errcode);
int PrintNode(Node *node);
int TreeSpecialSearch (Node *tree, KeyType *key, Node **ans, int *size);
int PrintTree(Node **tree);
int ReadTreefromFile(Node **tree, char *name);
int WriteTreeforGraph(Node **tree);

#endif
