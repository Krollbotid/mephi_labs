#include "dtree.h"
#include <stdlib.h>
#include <string.h>

int getInt(int start, int end, int *ans) {// get int in [start, end)
	char *errmsg = "";
	int k = 0;
	do {
		printf(errmsg);
		errmsg = "Incorrect input. Please try again.";
		k = scanf("%d", ans);
        if (k < 0) {
            return 3;
        }
		scanf("%*[^\n]");
		scanf("%*c");
	} while (!k || *ans >=end || *ans < start);
	return 0;
}

int getIntUnsized(int *ans) {//get int > 0
	char *errmsg = "";
	int k = 0;
	do {
		printf(errmsg);
		errmsg = "Incorrect input. Please try again.";
		k = scanf("%u", ans);
        if (k < 0) {
            return 3;
        }
		scanf("%*[^\n]");
		scanf("%*c");
	} while (!k || (*ans < 1));
	return 0;
}

int menu(const char *options[], const int N, int *id) {
    printf("Menu:\n");
	int i;
	for (i = 0; i < N; i++) {
		puts(options[i]);
	}
	printf("Print menu option number:");
	int errcode = getInt(0, N, id);
	if (errcode) {
		return errcode;
	}
	return 0;
}

char **errarray() {
	char **arr = (char**) malloc((23 + 1) * sizeof(char*));
	arr[0] = "Success";
	arr[1] = "Zero value in non-zero variable";
	arr[2] = "Out of memory";
	arr[3] = "End of file";
	arr[4] = "Not found";
	arr[11] = "Tree - can't elements with the same keys";
	arr[12] = "Tree - tree is empty! There is nothing to delete";
	arr[13] = "Tree is empty!";
	arr[14] = "Tree - error during reading";
	arr[15] = "Tree - can't open file";
	arr[21] = "Dialog - out of errmessages array";
	arr[22] = "Dialog - incorrect file name";
	arr[23] = "Dialog - incorrect input. Please try again.";
	return arr;
}

int errprint(int errcode, char **arr) {
	if (errcode > 23) {
		errcode = 21;
	}
	printf("%s\n", arr[errcode]);
	return 0;
}

int DTreeInsert(Tree *tree) {
	if (!tree) {
		return 1;
	}
	Node *node = (Node*) malloc(sizeof(Node));
	if (!node) {
		return 2;
	}
	node->key = readline("Write key (string):");
	if (!(node->key) || !(*(node->key))) {
		NodeDelete(node);
		return 23;
	}
	node->info = readline("Write info (string):");
	if (!(node->info) || !(*(node->info))) {
		NodeDelete(node);
		return 23;
	}
	int errcode = RB_Insert(tree, node);
	if (errcode) {
		return errcode;
	}
	return errcode;
}

int DTreeDelete(Tree *tree) {
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

int DTreeGoAround(Tree *tree) {
	if (!tree) {
		return 1;
	}
	KeyType *key = readline("Write key (string):");
	if (!key) {
		return 3;
	}
	int errcode = TreeGoAround(tree, key);
	free(key);
	return errcode;
}

int DTreeSearch(Tree *tree) {
	if (!tree) {
		return 1;
	}
	if (tree->EList == tree->root) {
		return 13;
	}
	KeyType *key = readline("Write key (string):");
	if (!key) {
		return 3;
	}
	int errcode = 0, size = 0;
	Node **arr = TreeSearch(tree, key, &size, &errcode);
	free(key);
	if (errcode) {
		return errcode;
	}
	int i;
	Node **ptr = arr;
	for (i = 0; i < size; i++) {
		printf("Number:%d ", i + 1);
		errcode = PrintNode(*ptr);
		if (errcode) {
			free(arr);
			return errcode;
		}
		ptr++;
	}
	free(arr);
	return 0;
}

int DTreeSpecialSearch(Tree *tree) {
	if (!tree) {
		return 1;
	}
	if (tree->EList == tree->root) {
		return 13;
	}
	KeyType *key = readline("Write key (string):");
	if (!key) {
		return 3;
	}
	int errcode = 0, size = 0;
	Node **arr = TreeSpecialSearch(tree, key, &size, &errcode);
	free(key);
	if (errcode) {
		free(arr);
		return errcode;
	}
	int i;
	Node **ptr = arr;
	for (i = 0; i < size; i++) {
		errcode = PrintNode(*ptr);
		if (errcode) {
			free(arr);
			return errcode;
		}
		ptr++;
	}
	free(arr);
	return 0;
}

int DReadTreefromFile(Tree *tree) {
	//char *name = "test.txt";
	char *name = readline("Please write name of file:");
	if (!name) {
		return 22;
	}
	int errcode = ReadTreefromFile(tree, name);
	free(name);
	return errcode;
}

int DWriteTreetoFile(Tree *tree) {
	//char *name = "test.txt";
	char *name = readline("Please write name of file:");
	if (!name) {
		return 22;
	}
	int errcode = WriteTreetoFile(tree, name);
	free(name);
	return errcode;
}

int DRandGenTree(Tree *tree) {
	int minlen, maxlen, amount;
	printf("Print min length of keys from [1; 20]:");
	getInt(1, 21, &minlen);
	printf("Print max length of keys from [1; 20]:");
	getInt(1, 21, &maxlen);
	printf("Print amount of elements:");
	getIntUnsized(&amount);
	randGenTree(tree, minlen, maxlen, amount);
	return 0;
}

int DTimer(Tree *tree) {
	int dotnumber, amount, multiplier;
	printf("Print amount of dots:");
	getIntUnsized(&dotnumber);
	printf("Print amount of tests:");
	getIntUnsized(&amount);
	printf("Print multiplier:");
	getIntUnsized(&multiplier);
	printf("Measures of search:\n");
	return SearchTimer(dotnumber, amount, multiplier);
}
