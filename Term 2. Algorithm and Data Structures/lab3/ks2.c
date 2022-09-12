#include <stdlib.h>
#include "ks2.h"
#include <stdio.h>

int keytohash(KeyType2 key, int msize2) {
    return (int) key % msize2;
    char *bytes = (void*) &key;
    int hash = 2147483647, i = 0;
    for (; i < sizeof(KeyType2); i++) {
        hash = 37 * hash + bytes[i];
    }
    return abs(hash) % msize2;
}

int ks2ArrCreate(int msize2, KeySpace2 **ans) {
    if (!msize2) {
        return 1;
    }
    KeySpace2 *arr = (KeySpace2*) malloc(msize2 * sizeof(KeySpace2)), *ptr = arr;
    if (!arr) {
        return 2;
    }
    int i = 0;
    for (; i < msize2; i++) {
        ptr->next = NULL;
        ptr++;
    }
    *ans = arr;
    return 0;
}

int ks2Delete (KeySpace2 *whom) {
	free(whom);
	return 0;
}

int ks2Insert(KeySpace2 *ks2, int msize2, Item *info, Item **ans) {
    if (!ks2 || !msize2 || !info) {
        return 1;
    }
    KeyType2 key = info->key2;
    KeySpace2 *ptr = ks2 + keytohash(key, msize2);
    while(ptr->next) {
        ptr = ptr->next;
        if (ptr->key == key) {
            if (ptr->info->key1 == info->key1) {
                *ans = ptr->info;
                return 0;
            }
            return 30;
        }
    }
    ptr->next = (KeySpace2*) malloc(sizeof(KeySpace2));
    if (!(ptr->next)) {
        return 2;
    }
    ptr->next->key = key;
    ptr->next->info = info;
    ptr->next->next = NULL;
	*ans = NULL;
    return 0;
}

int ks2Search(KeySpace2 *ks2, int msize2, KeyType2 key, Item **ans) {
    if (!ks2 || !msize2) {
        return 1;
    }
    KeySpace2 *ptr = ks2 + keytohash(key, msize2);
    ptr = ptr->next;
	if(!ptr) {
		return 4;
	}
    while(key != ptr->key) {
        ptr = ptr->next;
        if (!ptr) {
            return 4;
        }
    }
	*ans = ptr->info;
    return 0;
}

int ks2Remove(KeySpace2 *ks2, KeyType2 key, int msize2, Item **ans, int mode) { // mode == 0 remove first release, otherwise all releases
	if (!ks2 || !msize2) {
		return 1;
	}
	KeySpace2 *ptr = ks2 + keytohash(key, msize2), *ptr_prev = ptr;
	ptr = ptr->next;
    if (!ptr) {
        return 4;
    }
	while (key != ptr->key) {
		ptr_prev = ptr;
		ptr = ptr->next;
		if (!ptr) {
			return 4;
		}
	}
	*ans = ptr->info;
	if (ptr->info->next && !mode) {
		ptr->info = (*ans)->next;
	} else {
		ptr_prev->next = ptr->next;
		if (ks2Delete(ptr)) {
			return 32;
		}
	}
	return 0;
}

int ks2Clear(KeySpace2 *src, int msize2, int mode) {// 0 clear only KeySpace2, not 0 clear also Items
	if (!src) {
		return 0;
	}
	if (!msize2) {
		return 1;
	}
	int i = 0;
	KeySpace2 *ptr = src, *ptr2, *ptr_prev;
	for(; i < msize2; i++) {
        ptr2 = ptr->next;
	    while (ptr2) {
	    	ptr_prev = ptr2;
	    	ptr2 = ptr2->next;
	    	if (mode) {
	    		if (ItemClear(ptr_prev->info)) {
	    			return 6;
	    		}
	    	}
	    	if (ks2Delete(ptr_prev)) {
	    		return 6;
	    	}
	    }
        ptr++;
    }
	free(src);
	return 0;
}

int ks2Print(KeySpace2 *ks2, int msize2, char *nameoffile) {
	if (!ks2) {
		return 1;
	}
	printf("By KeySpace2:\n");
	int errcode, i;
	KeySpace2 *ptr;
	for (i = 0; i < msize2; i++) {
		ptr = ks2->next;
		while (ptr) {
			printf("Key:%d\n", ptr->key);
            printf("\n");
			errcode = ItemPrint(nameoffile, ptr->info);
			if (errcode) {
				return errcode;
			}
			ptr = ptr->next;
            printf("\n");
		}
		ks2++;
	}
	return 0;
}
