#include "dtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline(char *s) {
	printf("%s", s);
	char buf[80 + 1] = {0}; //#define bufsiz 80
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = scanf("%80[^\n]",buf);
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
			scanf("%*c");
		}
	} while (n > 0);
	if (len > 0){
		ans[len] = '\0';
	} else {
		ans = (char*) calloc(1, sizeof(char));
	}
	return ans;
}

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
	Node *ptr = *arr;
	for (i = 0; i < size; i++) {
		PrintNode(ptr);
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
		return errcode;
	}
	int i;
	Node *ptr = *arr;
	for (i = 0; i < size; i++) {
		PrintNode(ptr);
		ptr++;
	}
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