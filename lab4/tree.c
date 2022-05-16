#include "tree.h"
#include <string.h>

int TreeInsert(Node **tree, Node *node) {
	if (!tree) {
		return 1;
	}
	if(!(*tree)) {
		*tree = node;
		return 0;
	}
	Node *ptr = *tree, *par = NULL;
	while (ptr) {
		par = ptr;
		int k = strcmp(node->key; ptr->key);
		if (!k) {
			return 11;  // tree - can't elements with the same keys;
		}
		if (key > 0) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}
	if (strcmp(node->key, ptr->key) > 0) {
		par->right = node;
	} else {
		par->left = node;
	}
	node->par = par;
	return 0;
}

int TreeDelete(Node **tree, KeyType key) {
	if (!tree) {
		return 1;
	}
	if(!(*tree)) {
		return 12;  // tree - tree is empty! There is nothing to delete;
	}
	Node *ptr = *tree, *par = NULL;
	while (ptr) {
		int k  = strcmp(node->key; ptr->key);
		if (!k) {
			break;
		}
		if (k > 0) {
			ptr = ptr->right;
		} else {
			ptr = ptr-> left;
		}
	}
	if (!ptr) {
		return 4;
	}
	if (ptr->left) {
		if (ptr->right) {
			return 13;  // this node has right and left subtrees. It's not possible to delete it!
		}
		
	} else {
	}
}
