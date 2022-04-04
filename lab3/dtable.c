#include "dtable.h"
#include <stdlib.h>

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
	return 0;
}

char **errarray() {
	char **arr = (char**) malloc(667 * sizeof(char*));
	arr[0] = "Success";
	arr[1] = "Zero in non-zero argument";
	arr[2] = "Out of memory";
	arr[3] = "End of File";
	arr[11] = "Item - failed infotype delete";
	arr[12] = "Item - failed reltype delete";
	arr[13] = "Item - failed keytype1 delete";
	arr[20] = "ks1 restriction - no elements with the same keys";
	arr[21] = "ks1 restriction - element with parent key was not found";
	arr[22] = "ks1 - failed keyspace1 delete";
	arr[23] = "ks1 - new version\'s of element parent key is not the same as first version\'s of that element parent key";
	arr[30] = "ks2 restriction - no elements with the same keys";
	arr[32] = "ks2 - failed keyspace1 delete";
	arr[51] = "dialog - out of errmessages array";
	arr[404] = "element not found";
	arr[666] = "magic error";
	return arr;
}

int errprint(int errcode) {
	char **arr = errarray();
	if (errcode > 666) {
		errcode = 51;
	}
	printf("%s\n", arr[errcode]);
	return 0;
}

int dinsert(Table *table) {
	InfoType *info = (InfoType*) malloc(sizeof(InfoType));
	if (!info) {
		return 2;
	}
	Item *item = (Item*) malloc(sizeof(Item));
	if (!item) {
		free(info);
		return 2;
	}
	int k = -1, tbegin, tend, count;
	float divided;
	KeyType1 key1, par;
	KeyType2 key2;
	printf("Please input tbegin, tend, count, divided, key1, par, key2 in following format:\ntbegin/tend/count/divided/key1/par/key2\nInput:");
	while (k < 7) {
		k = scanf("%d/%d/%d/%f/%f/%f/%d", &tbegin, &tend, &count, &divided, &key1, &par, &key2);
		if (k < 0) {
			free(info);
			free(item);
			return 3;
		}
		if (k == 7) {
			break;
		}
		printf("\nIncorrect input. Please try again.\n");
	}
	info->tbegin = tbegin;
	info->count = count;
	info->divided = divided;
	info->tend = tend;
	item->info = info;
	item->key1 = key1;
	item->key2 = key2;
	item->next = NULL;
	int errcode = tabInsert(table, par, item);
	if (errcode) {
		ItemDelete(item);
	}
	return errcode;
}
