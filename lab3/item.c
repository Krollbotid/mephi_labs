#include "item.h"

int InfoTypeDelete(InfoType1 *whom) {
	return 1;
}

int RelTypeDelete(RelType *whom) {
	return 1;
}

int KeyType1Delete(KeyType1 *whom) {
	return 1;
}

int ItemDelete(Item *whom) {
	int status = 0;
	if (!(InfoTypeDelete(whom->info))) {
		status += 1;
	}
	if (!(RelTypeDelete(&(whom->release)))) {
		status += 2;
	}
	if (!(KeyType1Delete(&(whom->key1)))) {
		status += 4;
	}
	if (status) {
		return status + 10;
	}
	return 0;
}
