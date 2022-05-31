#include "tree.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

Tree TreeInit() {
	Tree tree;
	Node *EList = (Node*) calloc(1, sizeof(Node));
	EList->color = BLACK;
	EList->key = "EList";
	EList->info = NULL;
	EList->par = NULL;
	EList->left = NULL;
	EList->right = NULL;
	tree.EList = EList;
	tree.root = EList;
	return tree;
}

void ClearTREE(Tree *tree) {
	free(tree->EList);
	return;
}

Node *TreeMinNode(Node *EList, Node *node) {
	if (!node || node == EList) {
		return NULL;
	}
	while (node->left != EList) {
		node = node->left;
	}
	return node;
}

Node *TreeNextNode(Node *EList, Node *node) {
	if (node->right) {
		return TreeMinNode(EList, node->right);
	}
	Node *ptr = node->par;
	while (ptr != EList && node == ptr->right) {
		node = ptr;
		ptr = node->par;
	}
	return ptr;
}

int LeftRotate(Tree *tree, Node *node) {
	Node *right = node->right, *par = node->par;
	node->right = right->left;
	if (right->left != tree->EList) {
		right->left->par = node;
	}
	right->par = par;
	if (par == tree->EList) {
		tree->root = right;
	} else {
		if (par->left == node) {
			par->left = right;
		} else {
			par->right = right;
		}
	}
	right->left = node;
	node->par = right;
	return 0;
}

int RightRotate(Tree *tree, Node *node) {
	Node *left = node->left, *par = node->par;
	node->left = left->right;
	if (left->right != tree->EList) {
		left->right->par = node;
	}
	left->par = par;
	if (par == tree->EList) {
		tree->root = left;
	} else {
		if (par->right == node) {
			par->right = left;
		} else {
			par->left = left;
		}
	}
	left->right = node;
	node->par = left;
	return 0;
}

int NodeDelete(Node *node) {
	free(node->key);
	free(node->info);
	free(node);
	return 0;
}

int TreeInsert(Tree *tree, Node *node) {
	if (!tree) {
		return 1;
	}
	node->par = tree->EList;
	node->left = tree->EList;
	node->right = tree->EList;
	if(tree->root == tree->EList) {
		tree->root = node;
		return 0;
	}
	Node *ptr = tree->root, *par = NULL;
	while (ptr != tree->EList) {
		par = ptr;
		if (strcmp(node->key, ptr->key) < 0) {
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}
	if (strcmp(node->key, par->key) < 0) {
		par->left = node;
	} else {
		par->right = node;
	}
	node->par = par;
	return 0;
}

int RB_Insert_Fixup(Tree *tree, Node *node) {
	Node *par, *gpar, *uncle;
	while (node != tree->EList && node->par != tree->EList && node->par->color == RED) {
		par = node->par;
		gpar = par->par;
		if (par == gpar->left) {
			uncle = gpar->right;
			if (uncle != tree->EList && uncle->color == RED) {  //  case 1
				par->color = BLACK;
				uncle->color = BLACK;
				gpar->color = RED;
				node = gpar;
				continue;
			} else if (node == par->right) {  //  case 2
				node = par;
				LeftRotate(tree, node);
				par = node->par;
			}
			par->color = BLACK;  //  case 3
			gpar->color = RED;
			RightRotate(tree, gpar);
		} else {
			uncle = gpar->left;
			if (uncle != tree->EList && uncle->color == RED) {
				par->color = BLACK;
				uncle->color = BLACK;
				gpar->color = RED;
				node = gpar;
				continue;
			} else if (node == par->left) {
				node = par;
				RightRotate(tree, node);
				par = node->par;
			}
			par->color = BLACK;
			gpar->color = RED;
			LeftRotate(tree, gpar);
		}
	}
	tree->root->color = BLACK;
	return 0;
}

int RB_Insert(Tree *tree, Node *node) {
	TreeInsert(tree, node);
	node->color = RED;
	RB_Insert_Fixup(tree, node);
	return 0;
}

int RB_Delete_Fixup(Tree *tree, Node *node) {
	while (node != tree->EList && node != tree->root && node->color == BLACK) {
		Node *par = node->par; //  exists always because node != root
		if (node == par->left) {
			Node *sibling = par->right;
			if (sibling != tree->EList && sibling->color == RED) {  //  case 1
				sibling->color = BLACK;
				par->color = RED;
				LeftRotate(tree, par);
				sibling = par->right;
			}
			if (sibling->left->color == BLACK && sibling->right->color == BLACK) {  //  case 2
				sibling->color = RED;
				node = par;
			} else {
				if (sibling->right->color == BLACK) {  //  case 3
					sibling->color = RED;
					sibling->left->color = BLACK;
					RightRotate(tree, sibling);
					sibling = par->right;
				}
				sibling->color = par->color;  //  case 4
				par->color = BLACK;
				sibling->right->color = BLACK;
				LeftRotate(tree, par);
				node = tree->root;
			}
		}
		else {
			Node *sibling = par->left;
			if (sibling != tree->EList && sibling->color == RED) {  //  case 1
				sibling->color = BLACK;
				par->color = RED;
				RightRotate(tree, par);
				sibling = par->left;
			}
			if (sibling->right->color == BLACK && sibling->left->color == BLACK) {  //  case 2
				sibling->color = RED;
				node = par;
			} else {
				if (sibling->left->color == BLACK) {  //  case 3
					sibling->color = RED;
					sibling->right->color = BLACK;
					LeftRotate(tree, sibling);
					sibling = par->left;
				}
				sibling->color = par->color;  //  case 4
				par->color = BLACK;
				sibling->left->color = BLACK;
				RightRotate(tree, par);
				node = tree->root;
			}
		}
	}
	node->color = BLACK;
	return 0;
}

int TreeDelete(Tree *tree, KeyType *key) {
	if (!tree) {
		return 1;
	}
	if(tree->root == tree->EList) {
		return 12;  // tree - tree is empty! There is nothing to delete;
	}
	Node *x = tree->root;
	while (x) {
		int k  = strcmp(key, x->key);
		if (!k) {
			break;
		}
		if (k > 0) {
			x = x->right;
		} else {
			x = x->left;
		}
	}
	if (!x) {
		return 4;
	}
	Node *y;
	if (x->right == tree->EList || x->left == tree->EList) {
		y = x;
	} else {
		y = TreeNextNode(tree->EList, x);
	}
	if (y->color == BLACK) {
		RB_Delete_Fixup(tree, y);
	}
	PrintTree(tree);
	Node *p;
	if (y->left != tree->EList) {
		p = y->left;
	} else {
		p = y->right;
	}
	if (p && p != tree->EList) {
		p->par = y->par;
	}
	if (y->par == tree->EList) {
		tree->root = p;
	} else {
		if (y->par->left == y) {
			y->par->left = p;
		} else {
			y->par->right = p;
		}
	}
	free(x->key);
	free(x->info);
	if (y != x) {
		x->key = y->key;
		x->info = y->info;
	}
	free(y);
	return 0;
}

Node **recTreeSearch(Node *Elist, Node *node, Node **arr, int *size) {
	if (node->left && node->left != Elist && !(strcmp(node->left->key, node->key))) {
		arr = recTreeSearch(Elist , node->left, arr, size);
	}
	arr = (Node**) realloc(arr, (*size + 1) * sizeof(Node*));
	arr[*size] = node;
	*size = *size + 1;
	if (node->right && node->right != Elist && !(strcmp(node->right->key, node->key))) {
		arr = recTreeSearch(Elist , node->right, arr, size);
	}
	return arr;
}

Node **TreeSearch(Tree *tree, KeyType *key, int *size, int *errcode) {
	if (!tree) {
		*errcode = 1;
		return NULL;
	}
	if (tree->root == tree->EList) {
		*errcode = 13;
		return NULL;
	}
	Node *ptr = tree->root;
	while (ptr != tree->EList) {
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
	if (ptr == tree->EList) {
		*errcode = 4;
		return NULL;
	}
	Node **arr = recTreeSearch(tree->EList, ptr, NULL, size);
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
	char *arr[] = {
		"RED",
		"BLACK"
	};
	printf("Color:%s key:%s info:%s\n", arr[node->color], node->key, node->info);
	return 0;
}
int recGoandPrint(Node *EList, Node *node) {
	PrintNode(node);
	if (node->left != EList) {
		recGoandPrint(EList, node->left);
	}
	if (node->right != EList) {
		recGoandPrint(EList, node->right);
	}
	return 0;
}
int recGoandPrintbyKey(Node *EList, Node *node, KeyType *key) {
	int k = strcmp(node->key, key);
	if (k <= 0) {
		if (node->right != EList) {
			recGoandPrintbyKey(EList, node->right, key);
		}
	} else {
		PrintNode(node);
		if (node->left != EList) {
			recGoandPrintbyKey(EList, node->left, key);
		}
		if (node->right != EList) {
			recGoandPrintbyKey(EList, node->right, key);
		}
	}
	return 0;
}

int TreeGoAround(Tree *tree, KeyType *key) {
	if (!tree) {
		return 1;
	}
	if (tree->EList == tree->root) {
		return 13; // tree is empty!
	}
	printf("Printing tree:\n");
	if (!key || !(*key)) {
		recGoandPrint(tree->EList, tree->root);
	} else {
		recGoandPrintbyKey(tree->EList, tree->root, key);
	}
	return 0;
}

int recTreeClear(Node *EList, Node *node) {
	if (node->left != EList) {
		recTreeClear(EList, node->left);
	}
	if (node->right != EList) {
		recTreeClear(EList, node->right);
	}
	return NodeDelete(node);
}

int TreeClear(Tree *tree) {
	if (!tree) {
		return 1;
	}
	if (tree->EList == tree->root) {
		return 0;
	}
	recTreeClear(tree->EList, tree->root);
	tree->root = tree->EList;
	return 0;
}

Node **TreeSpecialSearch (Tree *tree, KeyType *key, int *size, int *errcode) {
	if (!tree || !key || !size) {
		*errcode = 1;
		return NULL;
	}
	if (tree->root == tree->EList) {
		*errcode = 13;
		return NULL;
	}
	Node *ptr = tree->root;
	while (ptr != tree->EList) {
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
	if (ptr == tree->EList) {
		*errcode = 4;
		return NULL;
	}
	Node **arr = (Node**) malloc(sizeof(Node*) * 2);
	if (ptr->left != tree->EList) {
		*arr = ptr->left;
		*size = *size + 1;
	} else if (ptr->par != tree->EList && ptr == ptr->par->right){
		*arr = ptr->par;
		*size = *size + 1;
	}
	if (ptr->right != tree->EList) {
		arr[*size] = ptr->right;
		*size = *size + 1;
	} else if (ptr->par != tree->EList && ptr == ptr->par->left){
		arr[*size] = ptr->par;
		*size = *size + 1;
	}
	return arr;
}

int recPrintbyLevel(Node *node, int depth) {
	if (node->left) {
		recPrintbyLevel(node->left, depth + 1);
	}
	int i;
	for (i = 0; i < depth; i++) {
		printf("   ");
	}
	if (node->color == RED) {
		printf("RED ");
	} else {
		printf("BLACK ");
	}
	printf("%s\n", node->key);
	if (node->right) {
		recPrintbyLevel(node->right, depth + 1);
	}
	return 0;
}

int PrintTree(Tree *tree) {
	if (!tree) {
		return 1;
	}
	if (tree->EList == tree->root) {
		return 13;
	}
	recPrintbyLevel(tree->root, 0);
	return 0;
}

int ReadTreefromFile(Tree *tree, char *name) {
	FILE *fp = fopen(name, "r");
	if (!fp) {
		return 15;
	}
	while (1) {
		Node *node = (Node*) malloc(sizeof(Node));
		node->info = NULL;
		node->key = freadline(fp);
		if (!(node->key) || !(*(node->key))) {
			NodeDelete(node);
			fclose(fp);
			return 0;
		}
		node->info = freadline(fp);
		if (!(node->info) || !(*(node->info))) {
			NodeDelete(node);
			fclose(fp);
			return 14;
		}
		int errcode = RB_Insert(tree, node);
		if (errcode) {
			return errcode;
		}
	}
}

int recWriteNodeforGraph(Node *Elist, Node *node, FILE *fp, int number) {
	if (node == Elist) {
		fprintf(fp, "\t%d [shape=box, label=\"%s\", style=filled, color=black, fontcolor=white];\n", number,  node->key);
	}
	if (node->color == RED) {
		fprintf(fp, "\t%d [label=\"%s\", color=red];\n", number,  node->key);
	} else {
		fprintf(fp, "\t%d [label=\"%s\", color=black];\n", number,  node->key);
	}
	if (node->left) {
		fprintf(fp, "\t%d -> %d;\n", number, 2 * number + 1);
		recWriteNodeforGraph(Elist, node->left, fp, 2 * number + 1);
	}
	if (node->right) {
		fprintf(fp, "\t%d -> %d;\n", number, 2 * number + 2);
		recWriteNodeforGraph(Elist, node->right, fp, 2 * number + 2);
	}
	return 0;
}

int WriteTreeforGraph(Tree *tree) {
	if (!tree) {
		return 1;
	}
	if (tree->EList == tree->root) {
		return 13;
	}
	FILE *fp = fopen("graph.dot", "w");
	if (!fp) {
		return 15;
	}
	fprintf(fp, "digraph G {\n");
	recWriteNodeforGraph(tree->EList, tree->root, fp, 0);
	fprintf(fp, "}");
	fclose(fp);
	system("dot -Tpng graph.dot -o graph.png");
	return 0;
}

int recWritetoFile(Node *EList, Node *node, FILE *fp) {
	if (node->left != EList) {
		recWritetoFile(EList, node->left, fp);
	}
	fprintf(fp, "%s\n%s\n", node->key, node->info);
	if (node->right != EList) {
		recWritetoFile(EList, node->right, fp);
	}
	return 0;
}

int WriteTreetoFile(Tree *tree, char *name) {
	FILE *fp = fopen(name, "w");
	if (!fp) {
		return 15;
	}
	recWritetoFile(tree->EList, tree->root, fp);
	fclose(fp);
	return 0;
}
