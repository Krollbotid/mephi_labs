#include "timing.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TESTNAMELEN 10

char *randString(int minlength, int maxlength) {
    //const int chbegin = 32, chend = 126; // From ASCII usable chars are [chbegin; chend]
    char allowed[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int chbegin = 0, chend = sizeof(allowed) / sizeof(allowed[0]);
    int i, len = 0;
	if (minlength == maxlength) {
		len = minlength;
	} else {
        len = scalerand(minlength, maxlength + 1);
    }
	char *str = (char*) malloc(sizeof(char) * (len + 1)), *ptr = str;
    for (i = 0; i < len; i++){
        *ptr = allowed[scalerand(chbegin, chend + 1) - 1];
		ptr++;
    }
    *ptr = '\0';
    return str;
}

Node *randNode(int minlength, int maxlength) {
    Node *node = (Node*) malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->par = NULL;
    node->key = randString(minlength, maxlength);
    node->info = NULL;
    return node;
}

int randGenTree(Tree *tree, int minlength, int maxlength, int amount) {
    int i, errcode;
    srand(time(NULL));
    for (i = 0; i < amount; i++){
        Node *node = randNode(minlength, maxlength);
		errcode = RB_Insert(tree, node);
		if (errcode) {
			return errcode;
		}
    }
    return errcode;
}

int SearchTimer(int dotnumber, int amount, int multiplier) {
    Tree test = TreeInit();
    int i, j, k, begin, len = scalerand(0, TESTNAMELEN + 1), errcode, number = 10000;
    char **arr = (char**) malloc(sizeof(char*) * number), **ptr = arr;
    for (i = 0; i < number; i++) {
        *ptr = randString(len, len);
        ptr++;
    }
    FILE *fp = fopen("measures.txt", "w");
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < multiplier; j++) {
        	Node *node = randNode(len, len);
	    	errcode = RB_Insert(&test, node);
		if (errcode) {
			return errcode;
		}
        }
        ptr = arr;
        for (k = 0; k < number; k++) {
            int size = 0;
            begin = clock();
            Node **arr = TreeSearch(&test, *ptr, &size, &errcode);
		if(errcode != 4 && errcode != 0) {
			TreeClear(&test);
			ClearTREE(&test);
			return errcode;
		}
            time += ((double) (clock() - begin)) / CLOCKS_PER_SEC;
            free(arr);
            ptr++;
        }
        fprintf(fp, "%lf\n", time);
        printf("Dot #%d. Amount:%d\tTime:%lf\n", i, multiplier * i, time);
    }
    ptr = arr;
    for (i = 0; i < number; i++) {
        free(*ptr);
        ptr++;
    }
    fclose(fp);
    free(arr);
    TreeClear(&test);
    ClearTREE(&test);
	return 0;
}
