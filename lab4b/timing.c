#include "timing.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TESTNAMELEN 10

char *randString(int minlength, int maxlength) {
    const int chbegin = 32, chend = 126; // From ASCII usable chars are [chbegin; chend]
    int i, len = 0;
	if (minlength == maxlength) {
		len = minlength;
	} else {
        len = scalerand(minlength, maxlength + 1);
    }
	char *str = (char*) malloc(sizeof(char) * (len + 1)), *ptr = str;
    for (i = 0; i < len; i++){
        *ptr = scalerand(chbegin, chend + 1);
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
    node->info = abs(rand());
    return node;
}

int randGenTree(Node **tree, int minlength, int maxlength, int amount) {
    int i, errcode;
	Info trash;
    srand(time(NULL));
    for (i = 0; i < amount; i++){
        Node *node = randNode(minlength, maxlength);
		errcode = TreeInsert(tree, node, &trash);
		if (errcode) {
			if (errcode == 11) {
				i--;
				errcode = 0;
			}
			NodeDelete(node);
			if (errcode) {
				return errcode;
			}
		}
    }
    return errcode;
}

int InsertTimer(int dotnumber, int amount, int multiplier) {
    Node *test = NULL;
    int i, k, begin, len = scalerand(0, TESTNAMELEN + 1), errcode;
    Info trash;
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (k = 0; k < multiplier * i; k++) {
            Node *node = randNode(len, len);
            begin = clock();
            errcode = TreeInsert(&test, node, &trash);
            time += ((double) (clock() - begin)) / CLOCKS_PER_SEC;
            if (errcode) {
                NodeDelete(node);
            }
        }
        TreeClear(&test);
        printf("Dot #%d. Amount:%d\tTime:%f\n", i, multiplier * i, time/amount);
    }
	return 0;
}

int DeleteTimer(int dotnumber, int amount, int multiplier) {
    Node *test = NULL;
    int i, j, k, begin, len = scalerand(0, TESTNAMELEN + 1);
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < amount; j++){
            randGenTree(&test, len, len, multiplier * i);
            for (k = 0; k < multiplier * i; k++) {
                char *key = randString(len, len);
                begin = clock();
                TreeDelete(&test, key);
                time += ((double) (clock() - begin)) / CLOCKS_PER_SEC;
                free(key);
            }
            TreeClear(&test);
        }
        printf("Dot #%d. Amount:%d\tTime:%f\n", i, multiplier * i, time/amount);
    }
	return 0;
}

int GoAroundTimer(int dotnumber, int amount, int multiplier) {
    Node *test = NULL;
    int i, j, begin, len = scalerand(0, TESTNAMELEN + 1);
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < amount; j++){
            randGenTree(&test, len, len, multiplier * i);
            begin = clock();
            recReverseGo(test);
            time += ((double) (clock() - begin)) / CLOCKS_PER_SEC;
            TreeClear(&test);
        }
        printf("Dot #%d. Amount:%d\tTime:%f\n", i, multiplier * i, time/amount);
    }
	return 0;
}

int SearchTimer(int dotnumber, int amount, int multiplier) {
    Node *test = NULL;
    int i, j, k, begin, len = scalerand(0, TESTNAMELEN + 1), errcode, number = 10000;
    char **arr = (char**) malloc(sizeof(char*) * number), **ptr = arr;
    for (i = 0; i < number; i++) {
        *ptr = randString(len, len);
        ptr++;
    }
    Info trash;
    FILE *fp = fopen("measures.txt", "w");
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < multiplier; j++) {
            Node *node = randNode(len, len);
	    	errcode = TreeInsert(&test, node, &trash);
	    	if (errcode) {
	    		if (errcode == 11) {
	    			j--;
	    			errcode = 0;
	    		}
	    		NodeDelete(node);
	    		if (errcode) {
	    			return errcode;
	    		}
	    	}
        }
        ptr = arr;
        for (k = 0; k < number; k++) {
            int size;
            begin = clock();
            Node **arr = TreeSearch(test, *ptr, &size, &errcode);
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
	return 0;
}

int SpecialSearchTimer(int dotnumber, int amount, int multiplier) {
    Node *test = NULL;
    int i, j, k, begin, len = scalerand(0, TESTNAMELEN + 1);
    for (i = 1; i <= dotnumber; i++){
        double time = 0;
        for (j = 0; j < amount; j++){
            randGenTree(&test, len, len, multiplier * i);
            for (k = 0; k < multiplier * i; k++) {
                char *key = randString(len, len);
                int size;
                Node **arr = (Node**) malloc(sizeof(Node*) * 2);
                begin = clock();
                TreeSpecialSearch(test, key, arr, &size);
                time += ((double) (clock() - begin)) / CLOCKS_PER_SEC;
                free(arr);
                free(key);
            }
            TreeClear(&test);
        }
        printf("Dot #%d. Amount:%d\tTime:%f\n", i, multiplier * i, time/amount);
    }
	return 0;
}