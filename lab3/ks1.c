#include <stdlib>

int ks1Insert(KeySpace1 *ks1, KeyType1 key, KeyType1 par, Item *info) {
	if (!ks1 || !info || !key) {
		return 1; // zero in non-zero argument
	}
	KeySpace1 *ptr = ks1;
	int parfound = 0;
	while (ptr->next) {
		if (ptr->key == key) {
			return 10; // ks1 restriction - no elements with the same keys
		}
		if (ptr->key == par) {
			parfound = 1;
		}
		ptr = ptr->next;
	}
	if (!parfound && par) {
		return 11; // ks1 restriction - element with parent key was not found
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
	return 0; //success
}

int ks1Search(KeySpace1 *ks1, KeyType1 key, KeySpace1 *ans) {
	if (!ks1 || !key) {
		return 1;
	}
	KeySpace1 *ptr = ks1;
	while (key != ptr->key) {
		ptr = ptr->next;
		if (!ptr) {
			return 404; //not found
		}
	}
	ans = ptr;
	return 0;
}

int ks1Delete(KeySpace1 *ks1, KeyType1 key) {
	if (!ks1 || !key) {
		return 1;
	}
	KeySpace1 ptr = ks1, ptr_prev = NULL;
	while (key != ptr->key) {
		ptr_prev = ptr;
		ptr = ptr->next;
		if (!ptr) {
			return 404;
		}
	}
	
}
