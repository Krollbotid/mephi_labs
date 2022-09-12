#include "tree.h"
#include <string.h>
#include <stdlib.h>

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
	} else {
		if (par->left == realptr) {
			par->left = subtree;
		} else {
			par->right = subtree;
		}
	}
	free(ptr->key);
	if (realptr != ptr) {
		ptr->key = realptr->key;
		ptr->info = realptr->info;
	}
	free(realptr);
	return 0;
}

Node **recTreeSearch(Node *node, Node **arr, int *size) {
	if (node->left && !(strcmp(node->left->key, node->key))) {
		arr = recTreeSearch(node->left, arr, size);
	}
	arr = (Node**) realloc(arr, (*size + 1) * sizeof(Node*));
	arr[*size] = node;
	*size = *size + 1;
	if (node->right && !(strcmp(node->right->key, node->key))) {
		arr = recTreeSearch(node->right, arr, size);
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
	Node **arr = recTreeSearch(tree, NULL, size);
	if (*errcode) {
		free(arr);
		arr = NULL;
	}
	return arr;
}

int PrintNode(Node *node) {
	if (!node) {
		return 1;
	}
	printf("key:%s info:%u\n", node->key, node->info);
	return 0;
}

int recReverseGo(Node *node) {
	if (node->left) {
		recReverseGo(node->left);
	}
	if (node->right) {
		recReverseGo(node->right);
	}
	return 0;
}

int recReverseGoandPrint(Node *node) {
	if (node->left) {
		recReverseGoandPrint(node->left);
	}
	if (node->right) {
		recReverseGoandPrint(node->right);
	}
	PrintNode(node);
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
	int count = 0, ansnum = -1;
	recTreeGoandMark(tree, &count, key, &ansnum);
	if (ansnum < 0) {
		return 4;
	}
	if (count == 1) {
		*ans = tree;
		return 0;
	}
	*size = 1;
	if (count - ansnum > ansnum - 1) {
		*ans = TreeMaxNode(tree);
	} else {
		*ans = TreeMinNode(tree);
		if (count - ansnum == ansnum - 1) {
			*size = *size + 1;
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
	if (!fp) {
		return 15;
	}
	while (1) {
		Node *node = (Node*) malloc(sizeof(Node));
		node->key = freadline(fp);
		if (!(node->key) || !(*(node->key))) {
			NodeDelete(node);
			fclose(fp);
			return 0;
		}
		int k = fscanf(fp, "%u", &(node->info));
		fscanf(fp, "%*[^\n]");
		fscanf(fp, "%*c");
		if (k < 1) {
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

int recWriteNodeforGraph(Node *node, FILE *fp) {
	if (node->left) {
		fprintf(fp, "\t%s -> %s;\n", node->key, node->left->key);
		recWriteNodeforGraph(node->left, fp);
	}
	if (node->right) {
		fprintf(fp, "\t%s -> %s;\n", node->key, node->right->key);
		recWriteNodeforGraph(node->right, fp);
	}
	return 0;
}

int WriteTreeforGraph(Node **tree) {
	if (!tree) {
		return 1;
	}
	if (!(*tree)) {
		return 13;
	}
	FILE *fp = fopen("graph.dot", "w");
	if (!fp) {
		return 15;
	}
	fprintf(fp, "digraph G {\n");
	recWriteNodeforGraph(*tree, fp);
	fprintf(fp, "}");
	fclose(fp);
	system("dot -Tpng graph.dot -o graph.png");
	return 0;
}

int recWritetoFile(Node *node, FILE *fp) {
	if (node->left) {
		recWritetoFile(node->left, fp);
	}
	fprintf(fp, "%s\n%u\n", node->key, node->info);
	if (node->right) {
		recWritetoFile(node->right, fp);
	}
	return 0;
}

int WriteTreetoFile(Node **tree, char *name) {
	FILE *fp = fopen(name, "w");
	if (!fp) {
		return 15;
	}
	recWritetoFile(*tree, fp);
	fclose(fp);
	return 0;
}
