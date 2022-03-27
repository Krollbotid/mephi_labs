#include <stdlib.h>
#include "ks1.h"

int ks1Delete (KeySpace1 *whom) {
	free(whom);
	return 0;
}

int ks1Insert(KeySpace1 *ks1, KeyType1 par, Item *info, Item **ans) {
	if (!ks1 || !info || !(info->key1)) {
		return 1; // zero in non-zero argument
	}
	KeyType1 key = info->key1;
	KeySpace1 *ptr = ks1;
	int parfound = 0;
	while (ptr->next) {
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
		}
		ptr = ptr->next;
	}
	if (!parfound && par) {
		return 21; // ks1 restriction - element with parent key was not found
	}
	ptr->next = (KeySpace1*) malloc(sizeof(KeySpace1));
	if (!(ptr->next)) {
		return 2; // out of memory
	}
	ptr = ptr->next;
	ptr->key = key;
	ptr->par = par;
	ptr->info = info;
	ptr->next = NULL;
	return 0; // success
}

int ks1Search(KeySpace1 *ks1, KeyType1 key, KeySpace1 **ans) {
	if (!ks1 || !key) {
		return 1;
	}
	KeySpace1 *ptr = ks1;
	while (key != ptr->key) {
		ptr = ptr->next;
		if (!ptr) {
			return 404; // element not found
		}
	}
	*ans = ptr;
	return 0;
}

int ks1Remove(KeySpace1 **ks1, KeyType1 key, Item **ans, int mode) { // mode == 0 remove first release, otherwise all releases
	if (!ks1 || !(*ks1) || !key) {
		return 1;
	}
	KeySpace1 *ptr = *ks1, *ptr_prev = NULL;
	while (key != ptr->key) {
		ptr_prev = ptr;
		ptr = ptr->next;
		if (!ptr) {
			return 404;
		}
	}
	if (ptr->info->next && !mode) {
		*ans = ptr->info;
		ptr->info = (*ans)->next;
	} else {
		if (ptr_prev) {
			ptr_prev->next = ptr->next;
			if (!ks1Delete(ptr)) {
				return 22;
			}
		} else {
			*ks1 = (*ks1)->next;
		}
	}
	return 0;
}
