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
	char **arr = (char**) malloc((22 + 1) * sizeof(char*));
	arr[0] = "Success";
	arr[1] = "Zero value in non-zero variable";
	arr[2] = "Out of memory";
	arr[3] = "End of file";
	arr[11] = "Tree - can't elements with the same keys";
	arr[12] = "Tree - tree is empty! There is nothing to delete";
	arr[13] = "Tree is empty!";
	arr[14] = "Tree - error during reading";
	arr[15] = "Tree - can't open file";
	arr[21] = "Dialog - out of errmessages array";
	arr[22] = "Dialog - incorrect file name";
	return arr;
}

int errprint(int errcode, char **arr) {
	if (errcode > 22) {
		errcode = 21;
	}
	printf("%s\n", arr[errcode]);
	return 0;
}

int DTreeInsert(Node **tree) {
	if (!tree) {
		return 1;
	}
	Node *node = (Node*) malloc(sizeof(Node));
	if (!node) {
		return 2;
	}
	node->key = readline("Write key (string):");
	int k = 0;
	char *errmsg = "";
	printf("Write info (unsigned int)");
	do {
		printf(errmsg);
		errmsg = "Incorrect input. Please try again.";
		k = scanf("%u", &(node->info));
        if (k < 0) {
			NodeDelete(node);
            return 3;
        }
		scanf("%*[^\n]");
		scanf("%*c");
	} while (!k);
	node->par = NULL;
	node->left = NULL;
	node->right = NULL;
	Info info;
	int errcode = TreeInsert(tree, node, &info);
	if (errcode) {
		if (errcode == 11) {
			printf("Info in node with key:%s has been replaced. Old info:%u\n", node->key, info);
			errcode = 0;
		}
		NodeDelete(node);
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

int DTreeSearch(Node **tree) {
	if (!tree) {
		return 1;
	}
	if (!(*tree)) {
		return 13;
	}
	KeyType *key = readline("Write key (string):");
	if (!key) {
		return 3;
	}
	int errcode = 0, size = 0;
	Node **arr = TreeSearch(*tree, key, &size, &errcode);
	free(key);
	if (errcode) {
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

int DTreeSpecialSearch(Node **tree) {
	if (!tree) {
		return 1;
	}
	if (!(*tree)) {
		return 13;
	}
	KeyType *key = readline("Write key (string):");
	if (!key) {
		return 3;
	}
	int errcode = 0, size = 0;
	Node **arr = (Node**) malloc(sizeof(Node*) * 2);
	if (!arr) {
		free(key);
		return 2;
	}
	errcode = TreeSpecialSearch(*tree, key, arr, &size);
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

int DReadTreefromFile(Node **tree) {
	//char *name = "test.txt";
	char *name = readline("Please write name of file:");
	if (!name) {
		return 22;
	}
	int errcode = ReadTreefromFile(tree, name);
	free(name);
	return errcode;
}

int DWriteTreetoFile(Node **tree) {
	//char *name = "test.txt";
	char *name = readline("Please write name of file:");
	if (!name) {
		return 22;
	}
	int errcode = WriteTreetoFile(tree, name);
	free(name);
	return errcode;
}

int DRandGenTree(Node **tree) {
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

int DTimer(Node **tree) {
	int dotnumber, amount, multiplier;
	printf("Print amount of dots:");
	getIntUnsized(&dotnumber);
	printf("Print amount of tests:");
	getIntUnsized(&amount);
	printf("Print multiplier:");
	getIntUnsized(&multiplier);
	printf("List of functions you can measure:\n");
	const char (*menuoptions[]) = {
		"0.Insert.",
		"1.Remove.",
		"2.Go around.",
		"3.Search.",
		"4.Special search"
	};
	const int N = sizeof(menuoptions) / sizeof(menuoptions[0]);
	int i;
	for (i = 0; i < N; i++) {
		puts(menuoptions[i]);
	}
	printf("Print id of function you want to measure:");
	int id;
	getInt(0, N + 1, &id);
	int (*Treefuncs[]) (int dotnumber, int amount, int multiplier) = {
		InsertTimer,
		DeleteTimer,
		GoAroundTimer,
		SearchTimer,
		SpecialSearchTimer
	};
	return Treefuncs[id](dotnumber, amount, multiplier);
}
