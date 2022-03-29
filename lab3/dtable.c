#include "dtable.h"

int menu(int *id) {
	*id = -1;
	while (*id < 0) {
		if(scanf("%d", id) < 0) {
			return 3;
		}
		if (*id >= 0){
			break;
		}
		printf("Incorrect input. Please try again.\n");
	}
	return 0
}

char **errarray(){
	char **arr = (char**) malloc(667 * sizeof(char*));
	//fill array with errmessages
	return arr;
}

int errprint(int errcode, char **arr) {
	if (errcode > 666) {
		errcode = 52;
	}
	printf("%s\n", arr[errcode]);
	return 0;
}

int dinsert(Table *table) {
	int k = -1, tbegin, tend, count;
	float divided;
	KeyType1 key1, par;
	KeyType2 key2;
	printf("Please input tbegin, tend, count, divided, key1, par, key2 in following format:\ntbegin/tend/count/divided/key1/par/key2\nInput:");
	while (k < 7) {
		k = scanf("%d/%d/%d/%f/%f/%f/%d", &tbegin, &tend, &count, &divided, &key1, &par, &key2);
		if (k < 0) {
			return 3;
		}
		if (k == 7) {
			break;
		}
		printf("Incorrect input. Please try again.\n");
	}
	InfoType *info = (InfoType*) malloc(sizeof(InfoType));
	if (!info) {
		return 2;
	}
	info ->
}
