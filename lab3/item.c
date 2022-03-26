#include "item.h"

int InfoTypeDelete(InfoType *whom) {
	return 0;
}

int RelTypeDelete(RelType *whom) {
	return 0;
}

int KeyType1Delete(KeyType1 *whom) {
	return 0;
}

int ItemDelete(Item *whom) {
	int status = 0;
	if (InfoTypeDelete(whom->info)) {
		return 11;
	}
	if (RelTypeDelete(&(whom->release))) {
		return 12;
	}
	if (KeyType1Delete(&(whom->key1))) {
		return 13;
	}
	return 0;
}

int ItemReleaseFixer(Item *first) {
	if (!first) {
		return 1;
	}
	Item *ptr = first;
	int i = 1;
	while (ptr) {
		ptr->release = i;
		i++;
		ptr = ptr->next;
	}
	return 0;
}
