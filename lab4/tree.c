#include "tree.h"
#include <string.h>
#include <stdio.h>

Node *TreeMinNode(Node *node) {
	if (!node) {
		return NULL;
	}
	while (node->left) {
		node = node->left;
	}
	return node;
}

Node *TreeNextNode(Node *node) {
	if (node->right) {
		return TreeMinNode(node->right);
	}
	Node *ptr = node->par;
	while (ptr && node == ptr->right) {
		node = ptr;
		ptr = node->par;
	}
	return ptr;
}

int NodeDelete(Node *node) {
	free(node->key);
	free(node);
	return 0;
}

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
		int k = strcmp(node->key, ptr->key);
		if (!k) {
			return 11;  // tree - can't elements with the same keys;
		}
		if (k > 0) {
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

int TreeDelete(Node **tree, KeyType *key) {
	if (!tree) {
		return 1;
	}
	if(!(*tree)) {
		return 12;  // tree - tree is empty! There is nothing to delete;
	}
	Node *ptr = *tree;
	while (ptr) {
		int k  = strcmp(node->key, ptr->key);
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
	Node *realptr;
	if (!(ptr->right && ptr->left)) {
		realptr = ptr;
	} else {
		realptr = TreeNextNode(ptr);
	}
	Node *subtree;
	if (realptr->left) {
		subtree = realptr->left;
	} else {
		subtree = realptr->right;
	}
	Node *par = realptr->par;
	if (subtree) {
		subtree->par = par;
	}
	if (!par) {
		*tree = subtree;
	}
	if (par->left == realptr) {
		par->left = subtree;
	} else {
		par->right = subtree;
	}
	if (realptr != ptr) {
		ptr->key = realptr->key;
	}
	NodeDelete(realptr);
	return 0;
}

int recGoandPrint(Node *node) {
	if (node->left) {
		recGoandPrint(node->left);
	}
	printf("key:%s info:%u\n", node->key, node->info);
	if (node->right) {
		recGoandPrint(node->right);
	}
	return 0;
}

int TreeGoAround(Node **tree) {
	if (!tree) {
		return 1;
	}
	if (!(*tree)) {
		return 13; // tree is empty!
	}
	printf("Printing tree:\n");
	recGoandPrint(tree);
	return 0;
}

int recTreeClear(Node *node) {
	if (node->left) {
		recTreeClear(node->left);
	}
	if (node->right) {
		recTreeClear(node->right);
	}
	return NodeDelete(node);
}

int TreeClear(Node **tree) {
	if (!tree || !(*tree)) {
		return 0;
	}
	recTreeClear(*tree);
	*tree = NULL;
	return 0;
}
