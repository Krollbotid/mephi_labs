#include "item.h"
#include <stdlib.h>
#include <stdio.h>

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
			return 6;
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
    newitem->release = first->release + 1;
	return 0;
}

int fInsertInfo(char *nameoffile, Item *item, InfoType *info) {
	if (!nameoffile || !item) {
		return 1;
	}
	FILE *fp = fopen(nameoffile, "r+b");
	if (!fp) {
		return 63;
	}
	int status = 1;
	if (fseek(fp, 0, SEEK_SET)) {
		fclose(fp);
		return 64;
	}
	if (fwrite(&status, sizeof(int), 1, fp) != 1) {
		fclose(fp);
		return 65;
	}
	if (fseek(fp, 0, SEEK_END)) {
		fclose(fp);
		return 64;
	}
	if (fwrite(info, sizeof(InfoType), 1, fp) != 1) {
		fclose(fp);
		return 65;
	}
	item->info = ftell(fp) - sizeof(InfoType);
	fclose(fp);
	return 0;
}

int fGetInfo(char *nameoffile, Item *item, InfoType *info) {
	if (!nameoffile || !item) {
		return 1;
	}
	FILE *fp = fopen(nameoffile, "r+b");
	if (!fp) {
		return 61;
	}
	int status;
	if (fseek(fp, item->info, SEEK_SET)) {
		fclose(fp);
		return 64;
	}
	if (fread(&status, sizeof(int), 1, fp) != 1) {
		fclose(fp);
		return 66;
	}
	if (!status) {
		fclose(fp);
		return 67;
	}
	if (fseek(fp, item->info, SEEK_SET)) {
		fclose(fp);
		return 64;
	}
	if (fread(info, sizeof(InfoType), 1, fp) != 1) {
		fclose(fp);
		return 66;
	}
	fclose(fp);
	return 0;
}

int InfoPrint(InfoType *info) {
	if (!info) {
		return 1;
	}
	printf("tend:%d tbegin:%d count:%d divided:%5.2f", info->tbegin, info->tend, info->count, info->divided);
	return 0;
}

int ItemPrint(char *nameoffile, Item *first) {
	if (!first) {
		return 1;
	}
	int errcode;
	printf("Key1:%5.2f Key2:%d\n", first->key1, first->key2);
	while (first) {
		printf("Release:%d ", first->release);
		InfoType info;
		errcode = fGetInfo(nameoffile, first, &info);
		if (errcode) {
			return errcode;
		}
		errcode = InfoPrint(&info);
		printf("\n");
		if (errcode) {
			return errcode;
		}
		first = first->next;
	}
	return 0;
}
