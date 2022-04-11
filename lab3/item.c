#include "item.h"
#include <stdlib.h>
#include <stdio.h>

int InfoTypeDelete(InfoType *whom) {
	free(whom);
	return 0;
}

int RelTypeDelete(RelType *whom) {
	return 0;
}

int KeyType1Delete(KeyType1 *whom) {
	return 0;
}

int KeyType2Delete(KeyType2 *whom) {
	return 0;
}

int ItemDelete(Item *whom) {
	if (InfoTypeDelete(whom->info)) {
		return 11;
	}
	if (RelTypeDelete(&(whom->release))) {
		return 12;
	}
	if (KeyType1Delete(&(whom->key1))) {
		return 13;
	}
	if (KeyType2Delete(&(whom->key2))) {
		return 14;
	}
	free(whom);
	return 0;
}

int ItemClear(Item *src) {
	if (!src) {
		return 0;
	}
	Item *ptr = src;
	while (src) {
		ptr = src;
		src = src->next;
		if (ItemDelete(ptr)) {
			return 666;
		}
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

int ItemReleaseInsert(Item *first, Item *newitem) {
	if (!first) {
		return 1;
	}
	while (first->next) {
		first = first->next;
	}
	first->next = newitem;
	return 0;
}

int InfoPrint(InfoType *info) {
	if (!info) {
		return 1;
	}
	printf("tend:%d tbegin:%d count:%d divided:%f", info->tbegin, info->tend, info->count, info->divided);
	return 0;
}

int ItemPrint(Item *first) {
	if (!first) {
		return 1;
	}
	int errcode;
	printf("Key1:%f Key2:%d\n", first->key1, first->key2);
	while (first) {
		printf("Release:%d ", first->release);
		errcode = InfoPrint(first->info);
		printf("\n");
		if (errcode) {
			return errcode;
		}
		first = first->next;
	}
	return 0;
}
