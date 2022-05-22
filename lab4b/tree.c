#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *freadline(FILE *fp) {
	char buf[80 + 1] = {0}; //#define bufsiz 80
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = fscanf(fp, "%80[^\n]",buf);
		if (n < 0){
			if(!ans){
				return NULL;
			}
		} else if (n > 0) {
			int buf_len = strlen(buf);
			int str_len = len + buf_len;
			ans = (char*) realloc(ans, (str_len + 1) * sizeof(char));
			strncpy(ans+len, buf, buf_len);
			len = str_len;
		} else {
			fscanf(fp, "%*c");
		}
	} while (n > 0);
	if (len > 0){
		ans[len] = '\0';
	} else {
		ans = (char*) calloc(1, sizeof(char));
	}
	return ans;
}

Node *TreeMinNode(Node *node) {
	if (!node) {
		return NULL;
	}
	while (node->left) {
		node = node->left;
	}
	return node;
}

Node *TreeMaxNode(Node *node) {
	if (!node) {
		return NULL;
	}
	while (node->right) {
		node = node->right;
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

int TreeInsert(Node **tree, Node *node, Info *info) {
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
			*info = ptr->info;
			ptr->info = node->info;
			return 11;  // tree - can't elements with the same keys;
		}
		if (k > 0) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}
	if (strcmp(node->key, par->key) > 0) {
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
		int k  = strcmp(key, ptr->key);
		if (!k) {
			break;
		}
		if (k > 0) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
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

Node **recTreeSearch(Node *node, Node **arr, int *size, int *errcode) {
	if (!node) {
		*errcode = 1;
		return NULL;
	}
	if (node->left && !(strcmp(node->left->key, node->key))) {
		arr = recTreeSearch(node->left, arr, size, errcode);
		if (errcode) {
			return NULL;
		}
	}
	arr = (Node**) realloc(arr, (*size + 1) * sizeof(Node*));
	arr[*size] = node->right;
	*size = *size + 1;
	if (node->left && !(strcmp(node->right->key, node->key))) {
		arr = recTreeSearch(node->right, arr, size, errcode);
		if (errcode) {
			return NULL;
		}
	}
	return arr;
}

Node **TreeSearch(Node *tree, KeyType *key, int *size, int *errcode) {
	if (!tree) {
		*errcode = 13;
		return NULL;
	}
	while (tree) {
		int k  = strcmp(key, tree->key);
		if (!k) {
			break;
		}
		if (k > 0) {
			tree = tree->right;
		} else {
			tree = tree->left;
		}
	}
	if (!tree) {
		*errcode = 4;
		return NULL;
	}
	Node **arr = recTreeSearch(tree, NULL, size, errcode);
	if (*errcode) {
		free(arr);
		arr = NULL;
	}
	return arr;
}

int PrintNode(Node *node) {
	printf("key:%s info:%u\n", node->key, node->info);
	return 0;
}

int recReverseGoandPrint(Node *node) {
	if (node->right) {
		recReverseGoandPrint(node->right);
	}
	PrintNode(node);
	if (node->left) {
		recReverseGoandPrint(node->left);
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
	recReverseGoandPrint(*tree);
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
	if (!tree) {
		return 1;
	}
	if (!(*tree)) {
		return 0;
	}
	recTreeClear(*tree);
	*tree = NULL;
	return 0;
}

int recTreeGoandMark (Node *node, int *count, KeyType *key, int *ans) {
	if (node->left) {
		recTreeGoandMark(node->left, count, key, ans);
	}
	*count = *count + 1;
	if (!(strcmp(key, node->key))) {
		*ans = *count;
	}
	if (node->right) {
		recTreeGoandMark(node->right, count, key, ans);
	}
	return 0;
}

int TreeSpecialSearch (Node *tree, KeyType *key, Node **ans, int *size) {
	if (!key || !ans) {
		return 1;
	}
	if (!tree) {
		return 13;
	}
	int count = 0, ansnum;
	recTreeGoandMark(tree, &count, key, &ansnum);
	if (count == 1) {
		*ans = tree;
		return 0;
	}
	if (count - ansnum > ansnum - 1) {
		*ans = TreeMaxNode(tree);
	} else {
		*ans = TreeMinNode(tree);
		if (count - ansnum == ansnum - 1) {
			ans++;
			*ans = TreeMaxNode(tree);
		}
	}
	return 0;
}

int recPrintbyLevel(Node *node, int depth) {
	if (node->left) {
		recPrintbyLevel(node->left, depth + 1);
	}
	int i;
	for (i = 0; i < depth; i++) {
		printf("   ");
	}
	printf("%s\n", node->key);
	if (node->right) {
		recPrintbyLevel(node->right, depth + 1);
	}
	return 0;
}

int PrintTree(Node **tree) {
	if (!tree) {
		return 1;
	}
	if (!(*tree)) {
		return 13;
	}
	recPrintbyLevel(*tree, 0);
	return 0;
}

int ReadTreefromFile(Node **tree, char *name) {
	FILE *fp = fopen(name, "r");
	while (1) {
		Node *node = (Node*) malloc(sizeof(Node));
		int k = fscanf(fp, "%u", &(node->info));
		fscanf(fp, "%*[^\n]");
		fscanf(fp, "%*c");
		if (!k) {
			free(node);
			fclose(fp);
			return 14;
		}
		if (k < 0) {
			free(node);
			fclose(fp);
			return 0;
		}
		node->key = freadline(fp);
		if (!(node->key)) {
			NodeDelete(node);
			fclose(fp);
			return 14;
		}
		Info info;
		node->left = NULL;
		node->right = NULL;
		node->par = NULL;
		int errcode = TreeInsert(tree, node, &info);
		if (errcode) {
			if (errcode == 11) {
				printf("Info in node with key:%s has been replaced. Old info:%u\n", node->key, info);
				errcode = 0;
			}
			NodeDelete(node);
			if (errcode) {
				return errcode;
			}
		}
	}
}