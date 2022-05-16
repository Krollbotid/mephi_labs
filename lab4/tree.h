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

#endif
