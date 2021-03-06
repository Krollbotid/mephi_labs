#include <stdlib.h>
#include "ks1.h"
#include <stdio.h>

int ks1Delete (KeySpace1 *whom) {
	free(whom);
	return 0;
}

int ks1InitCreate (KeySpace1 **where) {
	if (!where) {
		return 1;
	}
	*where = (KeySpace1*) malloc(sizeof(KeySpace1));
	if (!(*where)) {
		return 2;
	}
	(*where)->info = NULL;
	(*where)->next = NULL;
	return 0;
}

int ks1Insert(KeySpace1 **ks1, KeyType1 par, Item *info, Item **ans) {
	if (!ks1 || !info || !(info->key1)) {
		return 1; // zero in non-zero argument
	}
	KeyType1 key = info->key1;
	KeySpace1 *ptr = *ks1;
	if (!((*ks1)->info)) {
		if (par) {
			return 21;
		}
		ptr->key = key;
		ptr->par = par;
		ptr->info = info;
		ptr->next = NULL;
		*ans = NULL;
		return 0;
	}
	int parfound = 0;
	while (ptr) {
		if (ptr->key == key) {
			if (ptr->info->key2 == info->key2) {
				if (ptr->par == par) {
                	*ans = ptr->info;
					return 0;
				}
				return 23;
			}
			return 20; // ks1 restriction - no elements with the same keys
		}
		if (ptr->key == par) {
			parfound = 1;
			break;
		}
		ptr = ptr->next;
	}
	if (!parfound && par) {
		return 21; // ks1 restriction - element with parent key was not found
	}
	ptr = (KeySpace1*) malloc(sizeof(KeySpace1));
	if (!ptr) {
		return 2; // out of memory
	}
	ptr->next = *ks1;
	*ks1 = ptr;
	ptr->key = key;
	ptr->par = par;
	ptr->info = info;
	return 0; // success
}

int ks1Search(KeySpace1 *ks1, KeyType1 key, Item **ans) {
	if (!ks1 || !key) {
		return 1;
	}
	KeySpace1 *ptr = ks1;
	while (key != ptr->key) {
		ptr = ptr->next;
		if (!ptr) {
			return 4; // element not found
		}
	}
	*ans = ptr->info;
	return 0;
}

int ks1MakeParZero(KeySpace1 *ks1, KeyType1 par) {
	if (!ks1 || !par) {
		return 1;
	}
	while(ks1) {
		if (ks1->par == par) {
			ks1->par = 0;
		}
		ks1 = ks1->next;
	}
	return 0;
}

int ks1Remove(KeySpace1 **ks1, KeyType1 key, Item **ans, int mode, int makezero) { // mode == 0 remove first release, otherwise all releases
	if (!ks1 || !(*ks1) || !key) {
		return 1;
	}
	KeySpace1 *ptr = *ks1, *ptr_prev = NULL;
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
		if (ptr_prev) {
			ptr_prev->next = ptr->next;
		} else {
			*ks1 = (*ks1)->next;
		}
		if (ks1Delete(ptr)) {
			return 22;
		}
		if (makezero) {
			if (ks1MakeParZero(*ks1, key)) {
				return 6;
			}
		}
	}
	return 0;
}

int ks1Clear(KeySpace1 *src, int mode) {// 0 clear only KeySpace1, not 0 clear also Items
	if (!src) {
		return 0;
	}
	KeySpace1 *ptr = src;
	while (src) {
		ptr = src;
		src = src->next;
		if (mode) {
			if (ItemClear(ptr->info)) {
				return 6;
			}
		}
		if (ks1Delete(ptr)) {
			return 6;
		}
	}
	return 0;
}

int ks1Print(char *nameoffile, KeySpace1 *ks1) {
	if (!ks1) {
		return 1;
	}
	printf("By KeySpace1:\n");
	if(!(ks1->info)) {
        return 24;
	}
	int errcode;
	while (ks1) {
        printf("Key:%5.2f Parent key:%5.2f\n", ks1->key, ks1->par);
        printf("\n");
		errcode = ItemPrint(nameoffile, ks1->info);
		if (errcode) {
			return errcode;
		}
		ks1 = ks1->next;
        printf("\n");
	}
	return 0;
}
