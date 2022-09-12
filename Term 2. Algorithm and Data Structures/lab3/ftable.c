#include "ftable.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

KeySpace1 *makereverselist(KeySpace1 *src) {
	KeySpace1 *ans = NULL, *prev = NULL;
	while (src) {
		ans = (KeySpace1*) malloc(sizeof(KeySpace1));
		ans->next = prev;
		ans->info = src->info;
		ans->par = src->par; 
		/*ans->key = src->key;*/ // not needed in the program
		src = src->next;
		prev = ans;
	}
	return ans;
}

int writeTableStructure(Table *table) {
	if (!table || !(table->ks1) || !(table->infofile) || !(table->structurefile)) {
		return 1;
	}
	FILE *fp = fopen(table->structurefile, "w+b");
	if (!fp) {
		return 62;
	}
	KeySpace1 *ks1 = makereverselist(table->ks1), *ks1copy = ks1;
	int count = 0;
	if (!(ks1->info)) {
		fwrite(&count, sizeof(int), 1, fp);
		fclose(fp);
		return 0;
	}
	if (fwrite(&count, sizeof(int), 1, fp) != 1){
		fclose(fp);
		return 65;
	}
	while (ks1) {
		Item *item = ks1->info;
		while (item) {
			//printf("%d %d %f %f %d %p\n", item->info, item->release, item->key1, item->par, item->key2, item->next);
			fwrite(&(item->info), sizeof(item->info), 1, fp);
			fwrite(&(item->key1), sizeof(item->key1), 1, fp);
			fwrite(&(ks1->par), sizeof(ks1->par), 1, fp); // because item->par maybe outdated due to ks1MakeParZero
			fwrite(&(item->key2), sizeof(item->key2), 1, fp);
			count++;
			item = item->next;
		}
		ks1 = ks1->next;
	}
	ks1Clear(ks1copy, 0);
	if (fseek(fp, 0L, SEEK_SET)) {
		fclose(fp);
		return 64;
	}
	if (fwrite(&count, sizeof(int), 1, fp) != 1) {
		fclose(fp);
		return 65;
	}
	fclose(fp);
	return 0;
}

int readTableStructure(Table *table) {
	if (!table || !(table->ks1) || !(table->infofile) || !(table->structurefile)) {
		return 1;
	}
	if (table->status == 1) {
		return 68;
	}
	FILE *fs = fopen(table->structurefile, "rb");
	if (!fs) {
		return 61;
	}
	int count, i;
	if (fread(&count, sizeof(int), 1, fs) != 1) {
		fclose(fs);
		return 0;
	}
	for (i = 0; i < count; i++) {
		Item *item = (Item*) malloc(sizeof(Item));
		if (!item) {
			fclose(fs);
			return 2;
		}
		fread(&(item->info), sizeof(item->info), 1, fs);
		fread(&(item->key1), sizeof(item->key1), 1, fs);
		fread(&(item->par), sizeof(item->par), 1, fs);
		fread(&(item->key2), sizeof(item->key2), 1, fs);
		item->release = 0;
		item->next = NULL;
		//printf("%d %d %f %f %d %p\n", item->info, item->release, item->key1, item->par, item->key2, item->next);
		int errcode = tabInsert(table, item->par, item, 0, NULL);
		if (errcode) {
			free(item);
			fclose(fs);
			return errcode;
		}
	}
	fclose(fs);
	return 0;
}


int rewriteTableData(Table *table) {
	if (!table || !(table->ks1) || !(table->infofile) || !(table->structurefile)) {
		return 1;
	}
	char s[] = "a;ldsh;ogm;alemto";
	FILE *fp = fopen(table->infofile, "rb"), *fcopy = fopen(s, "wb");
	if (!fp) {
		return 62;
	}
	KeySpace1 *ks1 = table->ks1;
	int status = 0;
	if (!(ks1->info)) {
		fwrite(&status, sizeof(int), 1, fcopy);
		fclose(fp);
		fclose(fcopy);
		rename(s, table->infofile);
		return 0;
	}
	fseek(fcopy, sizeof(int), SEEK_SET);
	while (ks1) {
		Item *item = ks1->info;
		while (item) {	
			fseek(fp, item->info, SEEK_SET);
			InfoType info;
			if (fread(&(info.count), sizeof(info.count), 1, fp) != 1 ||
			fread(&(info.tbegin), sizeof(info.tbegin), 1, fp) != 1 ||
			fread(&(info.tend), sizeof(info.tend), 1, fp) != 1 ||
			fread(&(info.divided), sizeof(info.divided), 1, fp) != 1) {
				fclose(fp);
				fclose(fcopy);
				return 66;
			}
			item->info = ftell(fcopy);
			if (fwrite(&(info.count), sizeof(info.count), 1, fcopy) != 1 ||
			fwrite(&(info.tbegin), sizeof(info.tbegin), 1, fcopy) != 1 ||
			fwrite(&(info.tend), sizeof(info.tend), 1, fcopy) != 1 ||
			fwrite(&(info.divided), sizeof(info.divided), 1, fcopy) != 1) {
				fclose(fp);
				fclose(fcopy);
				return 65;
			}
			item = item->next;
		}
		ks1 = ks1->next;
	}
	printf("here\n");
	if (fseek(fcopy, 0, SEEK_SET)) {
		fclose(fp);
		fclose(fcopy);
		return 64;
	}
	status = 1;
	if (fwrite(&status, sizeof(int), 1, fcopy) != 1) {
		fclose(fp);
		fclose(fcopy);
		return 65;
	}
	fclose(fp);
	fclose(fcopy);
	rename(s, table->infofile);
	return 0;
}

int filechecks(char *namestruct, char *nameinfo) {
	FILE *fs = fopen(namestruct, "rb");
	if (!fs) {
		fs = fopen(namestruct, "wb");
	}
	fclose(fs);
	fs = fopen(nameinfo, "rb");
	if (!fs) {
		fs = fopen(nameinfo, "wb");
		int status = 0;
		if (fwrite(&status, sizeof(int), 1, fs) != 1) {
			fclose(fs);
			return 65;
		}
	}
	fclose(fs);
	return 0;
}