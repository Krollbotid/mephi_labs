#include "dtable.h"
#include <stdlib.h>
#include <stdio.h>

int getsizeofks2(int *size) {
    while (*size <= 0) {
        printf("Please, enter size of KeySpace2 (natural number):");
        if(scanf("%d", size) < 0) {
            return 3;
        }
        if (*size > 0){
            break;
        }
        scanf("%*[^\n]");
        printf("Incorrect input. Please try again.\n");
    }
    return 0;
}

int menu(int *id) {
    printf("Menu:\n0.Exit\n1.Insert into table.\n2.Remove out of table.\n3.Print table to console.\n4.Search elements by compound key.\n5.Search elements by non-compound key.\n6.Remove all elements by non-compound key.\n7.Recursive removing of elements by key1.\n8.Search all elements by parent key.\n");
	*id = -1;
	while (*id < 0 || *id > 8) {
        printf("Please, enter id of menu:");
		if(scanf("%d", id) < 0) {
			return 3;
		}
		if (*id >= 0 && *id <=8){
			break;
		}
        scanf("%*[^\n]");
		printf("Incorrect input. Please try again.\n");
	}
	return 0;
}

char **errarray() {
	char **arr = (char**) malloc(52 * sizeof(char*));
	arr[0] = "Success";
	arr[1] = "Zero in non-zero argument";
	arr[2] = "Out of memory";
	arr[3] = "End of File";
	arr[4] = "element not found";
	arr[6] = "magic error";
	arr[11] = "Item - failed infotype delete";
	arr[12] = "Item - failed reltype delete";
	arr[13] = "Item - failed keytype1 delete";
	arr[14] = "Item - failed keytype2 delete";
	arr[15] = "Item - failed pointertype1 delete";
	arr[20] = "ks1 restriction - no elements with the same keys";
	arr[21] = "ks1 restriction - element with parent key was not found";
	arr[22] = "ks1 - failed keyspace1 delete";
	arr[23] = "ks1 - new version\'s of element parent key is not the same as first version\'s of that element parent key";
    arr[24] = "ks1 - table is empty";
	arr[30] = "ks2 restriction - no elements with the same keys";
	arr[32] = "ks2 - failed keyspace1 delete";
	arr[51] = "dialog - out of errmessages array";
	return arr;
}

int errprint(int errcode, char **arr) {
	if (errcode > 52) {
		errcode = 51;
	}
	printf("%s\n", arr[errcode]);
	return 0;
}

int dInsert(Table *table) {
	if (!table) {
		return 1;
	}
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
	while (k < 7) {
        printf("Please input tbegin, tend, count, divided, key1, par, key2 in following format:\ntbegin/tend/count/divided/key1/par/key2\nWhere tbegin,tend,count,key2 are integer; divided,key1,par are float.\nInput:");
		k = scanf("%d/%d/%d/%f/%f/%f/%d", &tbegin, &tend, &count, &divided, &key1, &par, &key2);
		if (k < 0) {
			free(info);
			free(item);
			return 3;
		}
		if (k == 7) {
			break;
		}
        scanf("%*[^\n]");
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

int dRemove(Table *table) {
	if (!table) {
		return 1;
	}
	int k = -1;
	KeyType1 key1;
	KeyType2 key2;
	printf("Please input key1, key2 in following format:key1/key2\nInput:");
	while (k < 2) {
		k = scanf("%f/%d", &key1,  &key2);
		if (k < 0) {
			return 3;
		}
		if (k == 2) {
			break;
		}
        scanf("%*[^\n]");
		printf("\nIncorrect input. Please try again.\n");
	}
	int errcode = tabRemove(table, key1, key2, 0);
	return errcode;
}

int dSearch(Table *table) {
	if (!table) {
		return 1;
	}
	printf("Please input key1, key2 in following format:key1/key2\nInput:");
	int k = -1;
	KeyType1 key1;
	KeyType2 key2;
	while (k < 2) {
        k = scanf("%f/%d", &key1,  &key2);
        if (k < 0) {
                return 3;
        }
        if (k == 2) {
                break;
        }
        scanf("%*[^\n]");
        printf("\nIncorrect input. Please try again.\n");
    }
    int errcode = tabSearch(table, key1, key2);
	return errcode;
}

int dSearchAny(Table *table) {
	if (!table) {
		return 1;
	}
	printf("Please input mode. Mode 1 - search by key1, mode 2 - search by key2\nInput:");
	int k = -1, mode = -1;
	KeyType1 key1 = 0;
	KeyType2 key2 = 0;
	while (k < 1 || (mode > 2 || mode < 1)) {
		mode = -1;
	        k = scanf("%d", &mode);
        	if (k < 0) {
        	    	return 3;
        	}
        	if (k > 0 && (mode == 1 || mode == 2)) {
        	    	break;
        	}
        	scanf("%*[^\n]");
        	printf("\nIncorrect input. Please try again.\n");
    	}
	if (mode == 1) {
		printf("Please input key1 (float)\nInput:");
        	k = -1;
		while (k < 1) {
    	    k = scanf("%f", &key1);
    	    if (k < 0) {
    	        return 3;
    	    }
    	    if (k > 0) {
    	        break;
    	    }
        	scanf("%*[^\n]");
    	    printf("\nIncorrect input. Please try again.\n");
    	}
	} else {
		printf("Please input key2 (integer)\nInput:");
        k = -1;
		while (k < 1) {
    	    k = scanf("%d", &key2);
    	    if (k < 0) {
    	        return 3;
    	    }
    	    if (k > 0) {
    	        break;
    	    }
        	scanf("%*[^\n]");
    	    printf("\nIncorrect input. Please try again.\n");
    	}
	}
    int errcode = tabSearchAny(table, key1, key2, mode);
	return errcode;
}

int dRemoveAny(Table *table) {
    if (!table) {
        return 1;
    }
    printf("Please input mode. Mode 1 - search by key1, mode 2 - search by key2\nInput:");
    int k = -1, mode = -1, errcode;
    Item *ans;
    KeyType1 key1 = 0;
    KeyType2 key2 = 0;
    while (k < 1) {
        k = scanf("%d", &mode);
        if (k < 0) {
            return 3;
        }
        if (k > 0 && (mode == 1 || mode == 2)) {
            break;
        }
        scanf("%*[^\n]");
        printf("\nIncorrect input. Please try again.\n");
    }
    if (mode == 1) {
        printf("Please input key1 (float)\nInput:");
        k = -1;
        while (k < 1) {
            k = scanf("%f", &key1);
            if (k < 0) {
                return 3;
            }
            if (k > 0) {
                break;
            }
        	scanf("%*[^\n]");
            printf("\nIncorrect input. Please try again.\n");
        }
        errcode = ks1Search(table->ks1, key1, &ans);
        if (errcode) {
            return errcode;
        }
        key2 = ans->key2;
    } else {
        printf("Please input key2 (integer)\nInput:");
        k = -1;
        while (k < 1) {
            k = scanf("%d", &key2);
            if (k < 0) {
                return 3;
            }
            if (k > 0) {
                break;
            }
        	scanf("%*[^\n]");
            printf("\nIncorrect input. Please try again.\n");
        }
        errcode = ks2Search(table->ks2, table->msize2, key2, &ans);
        if (errcode) {
            return errcode;
        }
        key1 = ans->key1;
    }
    errcode = tabRemove(table, key1, key2, 1);
    return errcode;
}

int dparSearch(Table *table) {
    if (!table) {
        return 1;
    }
    printf("Please input parent key\nInput:");
    int k = -1;
    KeyType1 par;
    while (k < 1) {
        k = scanf("%f", &par);
        if (k < 0) {
            return 3;
        }
        if (k == 1) {
            break;
        }
        scanf("%*[^\n]");
        printf("\nIncorrect input. Please try again.\n");
    }
    int errcode = parSearch(table, par);
    return errcode;
}

int dmultRemove(Table *table) {
    if (!table) {
        return 1;
    }
    printf("Please input key1\nInput:");
    int k = -1;
    KeyType1 key1;
    while (k < 1) {
        k = scanf("%f", &key1);
        if (k < 0) {
            return 3;
        }
        if (k == 1) {
            break;
        }
        scanf("%*[^\n]");
        printf("\nIncorrect input. Please try again.\n");
    }
    int errcode = multRemove(table, key1);
    return errcode;
}
