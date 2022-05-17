#include "dtree.h"
#include <stdio.h>
#include <readline/readline.h>

char **errarray() {
	char **arr = (char**) malloc((13 + 1) * sizeof(char*));
	arr[0] = "Success";
	arr[1] = "Zero value in non-zero variable";
	arr[2] = "Out of memory";
	arr[3] = "End of file";
	arr[11] = "Tree - can't elements with the same keys";
	arr[12] = "Tree - tree is empty! There is nothing to delete";
	arr[13] = "Tree is empty!";
}

int DTreeInsert(Node **tree) {
	if (!tree) {
		return 1;
	}
	Node *node = (Node*) malloc(sizeof(Node));
	if (!node) {
		return 2;
	}
	Node->key = readline("Write key (string):");
	int k = 0;
	printf("Write info (unsigned integer):");
	while (!k) {
		k = scanf("%u", &(Node->info));
		if (k < 0) {
			NodeDelete(node);
			return 3;
		}
	}
	node->par = NULL;
	node->left = NULL;
	node->right = NULL;
	int errcode = TreeInsert(tree, node));
	if (errcode) {
		free(node);
	}
	return errcode;
}

int DTreeDelete(Node **tree) {
	if (!tree) {
		return 1;
	}
	KeyType *key = readline("Write key (string):");
	if (!key) {
		return 3;
	}
	int errcode = TreeDelete(tree, key);
	free(key);
	return errcode;
}
